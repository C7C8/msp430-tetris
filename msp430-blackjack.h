#pragma once
#include <msp430.h>
#include <peripherals.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "common.h"


#define SHUFFLE_ROUNDS 150
#define IS_NUM(card) ((card >= C2 && card <= C10) || (card >= D2 && card <= D10) || (card >= H2 && card <= H10) || (card >= S2 && card <= S10))
#define IS_FAC(card) ((card >= CJ && card <= CK) || (card >= DJ && card <= DK) || (card >= HJ && card <= HK) || (card >= SJ && card <= SK))
#define IS_ACE(card) (card == CA || card == DA || card == HA || card == SA)

typedef enum {NA=0, CA, C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CQ, CK,
            DA, D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DQ, DK,
            HA, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK,
            SA, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK
} Cards;


void blackjack(bool music);
static void getPlayerCardString(Cards* hand, char* buf, int n);
static void getMSPCardString(Cards* hand, char* buf, int n);
static unsigned char getHandValue(Cards* hand);
static unsigned char getMSPBet(Cards* hand);
