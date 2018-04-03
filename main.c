#include <msp430.h>
#include "common.h"
#include "msp430-tetris.h"
#include "msp430-blackjack.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    initLeds();
    configDisplay();
    configKeypad();
    configMusic();
    bool musicEnabled = true;
    unsigned char selection = 0;

    beepWelcome();
    while (true){
        //Draw game selection screen
        CLRSCR;
        WCENTR("MSP430 GAMES", 5);
        WLEFT("1. TETRIS", 15);
        WLEFT("2. BLACKJACK", 23);
        if (musicEnabled) //can't use sprintf, what?
            Graphics_drawString(&g_sContext, "MUSIC(#)?Y", AUTO_STRING_LENGTH, 36, 87, true);
        else
            Graphics_drawString(&g_sContext, "MUSIC(#)?N", AUTO_STRING_LENGTH, 36, 87, true);
        DRWSCR;

        //Process menu selections
        while (true){
            selection = getKey();
            if (selection == '1' || selection == '2' || selection == '#' || selection == '*')
                break;
        }
        switch (selection){
        case '1':
            tetris(musicEnabled);
            beepWelcome();
            break;
        case '2':
            blackjack(musicEnabled);
            beepWelcome();
            break;
        case '#':
            musicEnabled = !musicEnabled;
            break;
        }
    }

}
