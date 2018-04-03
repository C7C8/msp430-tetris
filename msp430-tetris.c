#include "msp430-tetris.h"

void tetris(bool music){
    CLRSCR;
    WCENTR("MSP430 TETRIS", 15);
    WCENTR("PORT BY C7C8", 30);
    WCENTR("PRESS * TO PLAY", 60);
    DRWSCR;
    while (getKey() != '*') {}

    unsigned char cKey = 'a';
    char res[50];
    tetris_game game; //memory not allocated until needed
    tetris_game* tg = &game;
    char board[ROWS][COLUMNS];
    while (1){
        beepStart();

        //Main game loop
        tg = tg_create(tg, (char*) board, ROWS, COLUMNS);
        if (music)
            playMusic(tetrisTheme, TETRIS_NOTE_COUNT, TETRIS_SPEED);
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

            CLRSCR;
            tetris_displayBoard(tg);

            //Print stats on right side
            char res[10];
            sprintf(res, "S:%d", tg->points);
            Graphics_drawStringCentered(&g_sContext, (uint8_t*)res, AUTO_STRING_LENGTH, 75, 5, OPAQUE_TEXT);;
            DRWSCR;
            swDelay(1);
        }
        stopMusic();

        //Inform the player of their loss
        CLRSCR;
        WCENTR("GAME OVER", 15);
        sprintf(res, "SCORE: %d", tg->points);
        WCENTR(res, 25);
        WCENTR("PLAY AGAIN? (*)", 50);
        WCENTR("RETURN? (#)", 58);
        DRWSCR;
        beepBad();

        char selection;
        while (true){
            selection = getKey();
            if (selection == '*')
                break;
            else if (selection == '#')
                return;
        }
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
