#pragma once
#include <msp430.h>
#include <peripherals.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "common.h"


#define SHUFFLE_ROUNDS 150

typedef enum {NA=0, CA, C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CQ, CK,
            DA, D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DQ, DK,
            HA, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK,
            SA, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK
} Cards;


void blackjack(bool music);
static void getPlayerCardString(Cards* hand, char* buf, int n);
static void getMSPCardString(Cards* hand, char* buf, int n);