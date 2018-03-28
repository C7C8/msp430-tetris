#include "common.h"

void swDelay(int loops)
{
    volatile unsigned int i,j;
    for (j = 0; j < loops; j++)
    {
        i = 30000 ;
        while (i > 0)
           i--;
    }
}

inline void beepWelcome(){
    //swdelay too long and I don't want to modify it
    BuzzerOn(64);
    swDelay(1);
    BuzzerOff();
    for (volatile int i = 0; i < 2500; i++);
    BuzzerOn(64);
    for (volatile int i = 0; i < 10000; i++);
    BuzzerOff();
    for (volatile int i = 0; i < 2500; i++);
    BuzzerOn(32);
    swDelay(2);
    BuzzerOff();
}

inline void beepStart(){
    BuzzerOn(32);
    swDelay(1);
    BuzzerOff();
}

inline void beepBad(){
    BuzzerOn(256);
    swDelay(3);
    BuzzerOff();
}
