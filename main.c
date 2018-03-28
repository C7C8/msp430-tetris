#include <msp430.h>
#include "peripherals.h"
#include "msp430-tetris.h"

/*
 * Tetris code (tetris.c/h is largely the work of Stephen Brennan (github.com/brenns10). MSP430
 * port created by C7C8 using the libraries provided by ECE2049 at Worcester Polytechnic
 * Institute.
 */

//Utility functions
void swDelay(int loops);
void displayBoard();

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    initLeds();
    configDisplay();
    configKeypad();
    configMusic();
    Graphics_clearDisplay(&g_sContext);
    tetris(false);
}

