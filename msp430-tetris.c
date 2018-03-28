#include "msp430-tetris.h"

void tetris(bool music){
    Graphics_drawStringCentered(&g_sContext, "MSP430 TETRIS", AUTO_STRING_LENGTH, 48, 15, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "PORT BY C7C8", AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "PRESS # TO PLAY", AUTO_STRING_LENGTH, 48, 60, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
    while (getKey() != '#') {}

    unsigned char cKey = 'a';
    char res[50];
    tetris_game game; //memory not allocated until needed
    tetris_game* tg = &game;
    char board[ROWS][COLUMNS];
    while (1){
        BuzzerOn(32);
        swDelay(1);
        BuzzerOff();

        //Main game loop
        tg = tg_create(tg, (char*) board, ROWS, COLUMNS);
        if (music)
            playMusic();
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
            tetris_displayBoard(tg);

            //Print stats on right side
            char res[10];
            sprintf(res, "S:%d", tg->points);
            Graphics_drawStringCentered(&g_sContext, res, AUTO_STRING_LENGTH, 75, 5, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
            swDelay(1);
        }
        stopMusic();

        //Inform the player of their loss
        Graphics_clearDisplay(&g_sContext);
        Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 48, 15, OPAQUE_TEXT);
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

static void tetris_displayBoard(tetris_game* tg){
    Graphics_Rectangle block;
    for (int iX = 0; iX < ROWS; iX++){ //inverted, because reasons
        for (int iY = 0; iY < COLUMNS; iY++){
            if (TC_IS_FILLED(tg_get(tg, iX, iY))){
                block.yMin = iX * TX_SIZE + VERTI_OFFSET; //reversed, because the screen is rotated.
                block.xMin = iY * TY_SIZE + HORIZ_OFFSET;
                block.xMax = block.xMin + BLOCK_X;
                block.yMax = block.yMin + BLOCK_Y;
                Graphics_drawRectangle(&g_sContext, &block);
            }
        }
    }

    //Draw border around the screen, because it looks good
    block.xMin = HORIZ_OFFSET - 2;
    block.yMin = VERTI_OFFSET - 2;
    block.xMax = COLUMNS * (TX_SIZE + 2); //wat? TODO CLEAN THIS GRAPHICS CODE
    block.yMax = ROWS * TY_SIZE + 6;
    Graphics_drawRectangle(&g_sContext, &block);
}
