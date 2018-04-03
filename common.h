#pragma once
#include "peripherals.h"
//Frequently used graphics functions
#define CLRSCR Graphics_clearDisplay(&g_sContext)
#define DRWSCR Graphics_flushBuffer(&g_sContext)
#define WCENTR(str, y) Graphics_drawStringCentered(&g_sContext, (uint8_t*)str, AUTO_STRING_LENGTH, 48, y, true)
#define WLEFT(str, y) Graphics_drawString(&g_sContext, (uint8_t*)str, AUTO_STRING_LENGTH, 2, y, true)

//Frequently used timing functions
#define DELAY_NOTE for(volatile int i = 0; i < 2500; i++)

//Utility functions
void swDelay(int loops);
void beepWelcome();
void beepStart();
void beepBad();
void beepVictory();
