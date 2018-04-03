#include "music.h"

#define NOTE_GAP_LOOPS 1000
int musicTick = 0;  //How many ticks left until the note is complete
int musicPos = 0;   //What array position we're in

Note tetrisTheme[TETRIS_NOTE_COUNT] = {{E5, E_NOTE},{B4, S_NOTE},{C5, S_NOTE},{D5, E_NOTE},{C5, S_NOTE},{B4, S_NOTE},{A4, E_NOTE},
                                       {A4, S_NOTE},{C5, S_NOTE},{E5, E_NOTE},{D5, S_NOTE},{C5, S_NOTE},{B4, E_NOTE},{B4, S_NOTE},
                                       {C5, S_NOTE},{D5, E_NOTE},{E5, E_NOTE},{C5, E_NOTE},{A4, E_NOTE},{A4, E_NOTE},{NONE, E_NOTE},
                                       {D5, E_NOTE},{F5, S_NOTE},{A5, E_NOTE},{G5, S_NOTE},{F5, S_NOTE},{E5, E_NOTE},{C5, S_NOTE},
                                       {E5, E_NOTE},{D5, S_NOTE},{C5, S_NOTE},{B4, E_NOTE},{B4, S_NOTE},{C5, S_NOTE},{D5, E_NOTE},
                                       {E5, E_NOTE},{C5, E_NOTE},{A4, E_NOTE},{A4, E_NOTE},{NONE, E_NOTE},
                                       {D5, E_NOTE},{F5, S_NOTE},{A5, E_NOTE},{G5, S_NOTE},{F5, S_NOTE},{E5, E_NOTE},{C5, S_NOTE},
                                       {E5, E_NOTE},{D5, S_NOTE},{C5, S_NOTE},{B4, E_NOTE},{B4, S_NOTE},{C5, S_NOTE},{D5, E_NOTE},
                                       {E5, E_NOTE},{C5, E_NOTE},{A4, E_NOTE},{A4, E_NOTE},{NONE, E_NOTE},
                                       {E4, Q_NOTE},{C4, Q_NOTE},{D4, Q_NOTE},{B3, Q_NOTE},{C4, Q_NOTE},{A3, Q_NOTE},{G3S, Q_NOTE},
                                       {B3, Q_NOTE},{E4, Q_NOTE},{C4, Q_NOTE},{D4, Q_NOTE},{B3, Q_NOTE},{C4, E_NOTE},
                                       {E4, Q_NOTE},{C4, Q_NOTE},{D4, Q_NOTE},{B3, Q_NOTE},{C4, Q_NOTE},{A3, Q_NOTE},{G3S, Q_NOTE},
                                       {B3, Q_NOTE},{E4, Q_NOTE},{C4, Q_NOTE},{D4, Q_NOTE},{B3, Q_NOTE},{C4, E_NOTE},{E4, E_NOTE},
                                       {A4, E_NOTE},{A4, E_NOTE},{G4S, Q_NOTE}, {NONE, Q_NOTE}};

Note* cMusic = NULL;
unsigned int cMusicLen = 0;

//Interrupt vector for playing music, since this needs to be done asynchronously
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(){
    if (musicTick == 0) { //add a small delay between notes
        BuzzerOff();
        for (volatile int i = 0; i < NOTE_GAP_LOOPS; i++);
    }
    BuzzerOn(HZTOB(cMusic[musicPos].note)); //Apply some transformations to get this into BuzzerOn() format

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

void playMusic(Note* music, unsigned int length, unsigned int speed){
    //Resets play position and enables interrupts, starting off the timer A interrupt
    musicTick = 0;
    musicPos = 0;
    cMusic = music;
    cMusicLen = length;

    //Timer A runs at 32768 Hz, convert bpm into the right value
    TA0CCR0 = 32768 / (speed * 16/60);

    __enable_interrupt();
}

void stopMusic(){
    __disable_interrupt();
}
