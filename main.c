#include <msp430.h>
#include "peripherals.h"
#include "msp430-tetris.h"
#include "msp430-blackjack.h"

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
    bool musicEnabled = true;
    unsigned char selection = 0;

    while (true){
        //Draw game selection screen
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawStringCentered(&g_sContext, "MSP430 GAMES", AUTO_STRING_LENGTH, 48, 5, true);
        Graphics_drawString(&g_sContext, "1. TETRIS", AUTO_STRING_LENGTH, 2, 15, true);
        Graphics_drawString(&g_sContext, "2. BLACKJACK", AUTO_STRING_LENGTH, 2, 23, true);
        if (musicEnabled) //can't use sprintf, what?
            Graphics_drawString(&g_sContext, "MUSIC(#)?Y", AUTO_STRING_LENGTH, 36, 87, true);
        else
            Graphics_drawString(&g_sContext, "MUSIC(#)?N", AUTO_STRING_LENGTH, 36, 87, true);
        Graphics_flushBuffer(&g_sContext);
        beepWelcome();

        //Process menu selections
        while (true){
            selection = getKey();
            if ((selection >= '0' && selection <= '9') || selection == '#' || selection == '*')
                break;
        }
        switch (selection){
        case '1':
            tetris(musicEnabled);
            break;
        case '2':
            blackjack(musicEnabled);
            break;
        case '#':
            musicEnabled = !musicEnabled;
            break;
        }
    }

}
