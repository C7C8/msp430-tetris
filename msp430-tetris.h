#pragma once
#include <msp430.h>
#include <stdio.h>
#include <stdbool.h>
#include "peripherals.h"
#include "tetris.h"
#include "common.h"
#include "music.h"

#define BLOCK_X 2
#define BLOCK_Y 2
#define GAP 2
#define TX_SIZE (BLOCK_X + GAP)
#define TY_SIZE (BLOCK_Y + GAP)
#define HORIZ_OFFSET 20
#define VERTI_OFFSET 6

void tetris(bool music);
static void tetris_displayBoard(tetris_game* tg);
