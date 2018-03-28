#include "msp430-blackjack.h"

void blackjack(bool music){

    //Display welcome screen
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "MSP430 BLACKJACK", AUTO_STRING_LENGTH, 48, 15, true);
    Graphics_drawStringCentered(&g_sContext, "BY C7C8", AUTO_STRING_LENGTH, 48, 30, true);
    Graphics_drawStringCentered(&g_sContext, "PRESS * TO PLAY", AUTO_STRING_LENGTH, 48, 60, true);
    Graphics_flushBuffer(&g_sContext);
    while (getKey() != '*');
    beepStart();


    return;
}
