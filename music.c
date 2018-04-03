#include <msp430.h>
#include "peripherals.h"

#define TETRIS_NOTE_COUNT 115
#define NOTE_GAP_LOOPS 1000
int musicTick = 0;  //How many ticks left until the note is complete
int musicPos = 0;   //What array position we're in

unsigned char tetrisTheme[TETRIS_NOTE_COUNT][2] = {{23,2},{48,4},{36,2},{38,2},{43,2},{48,1},{43,1},{38,2},{36,2},
                                  {32,4},{32,2},{38,2},{48,4},{43,2},{38,2},{36,6},{38,2},{43,4},
                                  {48,4},{38,4},{32,4},{32,4},{0,2},{43,4},{51,2},{64,4},{57,2},
                                  {51,2},{48,6},{38,2},{48,4},{43,2},{38,2},{36,4},{36,2},{38,2},
                                  {43,4},{48,4},{38,4},{32,4},{32,4},{0,4},{48,4},{36,2},{38,2},
                                  {43,2},{48,1},{43,1},{38,2},{36,2},{32,4},{32,2},{38,2},{48,4},
                                  {43,2},{38,2},{36,6},{38,2},{43,4},{48,4},{38,4},{32,4},{32,4},
                                  {0,2},{43,4},{51,2},{64,4},{57,2},{51,2},{48,6},{38,2},{48,4},
                                  {43,2},{38,2},{36,4},{36,2},{38,2},{43,4},{48,4},{38,4},{32,4},
                                  {32,4},{0,4},{24,8},{19,8},{21,8},{18,8},{19,8},{16,8},{15,8},
                                  {18,8},{24,8},{19,8},{21,8},{18,8},{19,4},{24,4},{32,8},{30,1},
                                  {24,8},{19,8},{21,8},{18,8},{19,8},{16,8},{15,8},{18,8},{24,8},
                                  {19,8},{21,8},{18,8},{19,4},{24,4},{32,8},{30,16}};

unsigned char cMusic** = NULL;
unsigned int cMusicLen = 0;



//Interrupt vector for playing music, since this needs to be done asynchronously
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(){
    if (musicTick == 0) { //add a small delay between notes
        BuzzerOff();
        for (volatile int i = 0; i < NOTE_GAP_LOOPS; i++);
    }
    BuzzerOn((64-cMusic[musicPos][0]) * 3); //Apply some transformations to get this into BuzzerOn() format

    musicTick++;
    if (musicTick == cMusic[musicPos][1]){
        musicTick = 0;
        musicPos++;
    }
    if (musicPos == cMusicLen)
        musicPos = 0;
}

void configMusic(){
    //Configure timer A for stupid stuff
    TA0CCR0 = 22000; //10000 = 12.5 hz?
    TA0CCTL0 = CCIE;
    TA0CTL = MC_1 | ID_3 | TASSEL_2 | TACLR;
}

void playMusic(unsigned char music[][], unsigned int length){
    //Resets play position and enables interrupts, starting off the timer A interrupt
    musicTick = 0;
    musicPos = 0;
    cMusic = music;
    cMusicLen = length;
    __enable_interrupt();
}

void stopMusic(){
    __disable_interrupt();
}
