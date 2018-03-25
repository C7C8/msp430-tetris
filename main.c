#include <msp430.h>
#include <stdio.h>
#include "peripherals.h"
#include "tetris.h"

/*
 * Tetris code is largely the work of Stephen Brennan (github.com/brenns10). MSP430
 * port created by C7C8 using the libraries provided by ECE2049 at Worcester Polytechnic
 * Institute.
 */

#define BLOCK_X 2
#define BLOCK_Y 2
#define GAP 2
#define TX_SIZE (BLOCK_X + GAP)
#define TY_SIZE (BLOCK_Y + GAP)
#define HORIZ_OFFSET 20
#define VERTI_OFFSET 6

//Utility functions
void swDelay(char numLoops);
void displayBoard();

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    initLeds();
    configDisplay();
    configKeypad();
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "MSP430 TETRIS", AUTO_STRING_LENGTH, 48, 15, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "PORT BY C7C8", AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "PRESS # TO PLAY", AUTO_STRING_LENGTH, 48, 60, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
    while (getKey() != '#') {}

    unsigned char cKey = 'a';
    char res[50];
    tetris_game* tg;
    while (1){
        BuzzerOn(32);
        swDelay(1);
        BuzzerOff();

        //Main game loop
        tg = tg_create(ROWS, COLUMNS);
        while (1){
            tetris_move move = TM_NONE;
            cKey = getKey();
            switch(cKey){
            case '4':
                move = TM_LEFT;
                break;
            case '6':
                move = TM_RIGHT;
                break;
            case '2':
                move = TM_CLOCK;
                break;
            case '5':
                move = TM_DROP;
                break;
            }

            //Restart game if the player lost
            if (!tg_tick(tg, move))
                break;

            Graphics_clearDisplay(&g_sContext);
            displayBoard();

            //Print stats on right side
            char res[10];
            sprintf(res, "S:%d", tg->points);
            Graphics_drawStringCentered(&g_sContext, res, AUTO_STRING_LENGTH, 75, 5, OPAQUE_TEXT);
            sprintf(res, "L:%d", tg->level);
            Graphics_drawStringCentered(&g_sContext, res, AUTO_STRING_LENGTH, 75, 15, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(1);
        }

        //Inform the player of their loss
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawStringCentered(&g_sContext, "YOU LOSE", AUTO_STRING_LENGTH, 48, 15, OPAQUE_TEXT);
        sprintf(res, "SCORE: %d", tg->points);
        Graphics_drawStringCentered(&g_sContext, res, AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
        Graphics_drawStringCentered(&g_sContext, "PLAY AGAIN? (#)", AUTO_STRING_LENGTH, 48, 50, OPAQUE_TEXT);
        Graphics_flushBuffer(&g_sContext);
        BuzzerOn(256);
        swDelay(3);
        BuzzerOff();
        while (getKey() != '#') {}
    }
}

void displayBoard(){
    Graphics_Rectangle block;
    for (int iX = 0; iX < ROWS; iX++){ //inverted, because reasons
        for (int iY = 0; iY < COLUMNS; iY++){
            if (TC_IS_FILLED(tg_get(&tg_instance, iX, iY))){
                block.yMin = iX * TX_SIZE + VERTI_OFFSET; //reversed, because the screen is rotated.
                block.xMin = iY * TY_SIZE + HORIZ_OFFSET;
                block.xMax = block.xMin + BLOCK_X;
                block.yMax = block.yMin + BLOCK_Y;
                Graphics_drawRectangle(&g_sContext, &block);
            }
        }
    }
}

void swDelay(char numLoops)
{
	volatile unsigned int i,j;
	for (j=0; j<numLoops; j++)
    {
    	i = 30000 ;
   	    while (i > 0)
	       i--;
    }
}
