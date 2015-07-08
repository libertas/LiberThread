#define USE_ARDUINO
#include "liberthread.h"


static void thread(lt *pt, int pin, unsigned long time) 
{ 
  LT_BEGIN(pt); 
  while(1) {   
    LT_DELAY(pt, time);
    digitalWrite(pin,HIGH);
    LT_DELAY(pt, 500);
    digitalWrite(pin, LOW);
  } 
  LT_END(pt); 
} 


static lt pt1, pt2;
void setup()
{ 
  pinMode(8,OUTPUT);
  pinMode(13,OUTPUT);
  LT_INIT(&pt1); 
  LT_INIT(&pt2); 
}

void loop ()
{ 
  thread(&pt1, 8, 5000);
  thread(&pt2, 13, 500);
}



