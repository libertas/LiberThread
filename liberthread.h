/*
 * Developed by Romulus Libertas (horizonvei@gmail.com) in 2015
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef __LT_H__
#define __LT_H__

#define LT_WAITING ((void*) 0)
#define LT_DEAD ((void*) 1)

typedef void *location_t;

#ifndef USE_ARDUINO

struct liberthread
{
	location_t lc;  // The location where the thread stopped last time
};

typedef struct liberthread lt;

#endif

#define LT_INIT(lt) ((lt)->lc) = LT_WAITING

#define LT_EXIT(lt)\
	do {\
		((lt)->lc)= LT_DEAD;\
		return;\
	} while(0)

#define LT_BEGIN(lt)\
	if((lt)->lc==LT_WAITING) {

#define LT_END(lt)\
	}\
	else if((lt)->lc != LT_DEAD) {\
		goto *((lt)->lc);\
	}

#define LT_CONCAT2(s1, s2) s1##s2
#define LT_CONCAT(s1, s2) LT_CONCAT2(s1, s2)

#define LT_WAIT_FOR(lt, condition)\
	do {\
		LT_CONCAT(LINE, __LINE__):\
		if(!(condition)) {\
			(lt)->lc = &&LT_CONCAT(LINE, __LINE__);\
			return;\
		}\
	} while(0)

#endif

#ifdef USE_ARDUINO

struct liberthread
{
	location_t lc;  // The location where the thread stopped last time
	unsigned long t;
};

typedef struct liberthread lt;

#define LT_DELAY(lt, time)\
	do {\
		((lt)->t) = millis();\
		LT_WAIT_FOR(lt, millis()-((lt)->t) >= time);\
	} while(0)

#define LT_MICRODELAY(lt, time)\
	do {\
		((lt)->t) = micros();\
		LT_WAIT_FOR(lt, millis()-((lt)->t) >= time);\
	} while(0)

#endif
