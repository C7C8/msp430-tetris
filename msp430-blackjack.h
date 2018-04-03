#pragma once
#include <msp430.h>
#include <peripherals.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "common.h"
#include "music.h"

#define SHUFFLE_ROUNDS 150
#define IS_NUM(card) ((card >= CC2 && card <= CC10) || (card >= DD2 && card <= DD10) || (card >= H2 && card <= H10) || (card >= S2 && card <= S10))
#define IS_FAC(card) ((card >= CJ && card <= CK) || (card >= DJ && card <= DK) || (card >= HJ && card <= HK) || (card >= SJ && card <= SK))
#define IS_ACE(card) (card == CA || card == DA || card == HA || card == SA)

typedef enum {NA=0, CA, CC2, CC3, CC4, CC5, CC6, CC7, CC8, CC9, CC10, CJ, CQ, CK, //extra C's and D's to avoid conflicting with music.h's defines
            DA, DD2, DD3, DD4, DD5, DD6, DD7, DD8, DD9, DD10, DJ, DQ, DK,
            HA, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK,
            SA, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK
} Cards;

void blackjack(bool music);
static void getPlayerCardString(Cards* hand, char* buf, int n);
static void getMSPCardString(Cards* hand, char* buf, int n);
static unsigned char getHandValue(Cards* hand);
static unsigned char getMSPBet(Cards* hand);
