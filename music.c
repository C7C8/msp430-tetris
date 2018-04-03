#include "music.h"

#define NOTE_GAP_LOOPS 1000
int musicTick = 0;  //How many ticks left until the note is complete
int musicPos = 0;   //What array position we're in

Note tetrisTheme[TETRIS_NOTE_COUNT] = {{23,2},{48,4},{36,2},{38,2},{43,2},{48,1},{43,1},{38,2},{36,2},
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

Note* cMusic = NULL;
unsigned int cMusicLen = 0;

//Interrupt vector for playing music, since this needs to be done asynchronously
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(){
    if (musicTick == 0) { //add a small delay between notes
        BuzzerOff();
        for (volatile int i = 0; i < NOTE_GAP_LOOPS; i++);
    }
    BuzzerOn((64-cMusic[musicPos].note) * 3); //Apply some transformations to get this into BuzzerOn() format

    musicTick++;
    if (musicTick == cMusic[musicPos].length){
        musicTick = 0;
        musicPos++;
    }
    if (musicPos == cMusicLen)
        musicPos = 0;
}

void configMusic(){
    //Configure timer A
    TA0CCR0 = 22000; //10000 = 12.5 hz?
    TA0CCTL0 = CCIE;
    TA0CTL = MC_1 | ID_3 | TASSEL_2 | TACLR;
}

void playMusic(Note* music, unsigned int length, unsigned int bpm){
    //Resets play position and enables interrupts, starting off the timer A interrupt
    musicTick = 0;
    musicPos = 0;
    cMusic = music;
    cMusicLen = length;

    //Timer A runs at 32768 Hz, convert bpm into the right value
    TA0CCR0 = 32768 / (bpm * 16/60);

    __enable_interrupt();
}

void stopMusic(){
    __disable_interrupt();
}
