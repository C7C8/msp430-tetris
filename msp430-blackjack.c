#include "msp430-blackjack.h"

const char* CardsLookup[] = {"  ", "CA", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CJ", "CQ", "CK", //CA instead of C10 because 1) consistency in sizing, and 2) hex.
                       "DA", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DA", "DJ", "DQ", "DK",
                       "HA", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "HA", "HJ", "HQ", "HK",
                       "SA", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "SA", "SJ", "SQ", "SK",
};

void blackjack(bool music){

    //Display welcome screen
    CLRSCR;
    WCENTR("MSP430 BLACKJACK", 15);
    WCENTR("BY C7C8", 30);
    WCENTR("PRESS * TO PLAY", 60);
    DRWSCR;
    while (getKey() != '*');
    beepStart();

    //Seed the random number generator/ "cut the deck"
    {
        char input[3] = "00";
        char selection = '\0';
        CLRSCR;
        while (true){
            WCENTR("CUT THE DECK", 5);
            WCENTR("ENTER NUMBER", 13);
            WCENTR("1-5, * TO FINISH", 21);
            WCENTR(input, 29);
            DRWSCR;

            while (true){
                selection = getKey();
                if ((selection >= '0' && selection <= '9') || selection == '*')
                    break;
            }

            if (selection != '*'){
                input[0] = input [1];
                input[1] = selection; //ooh that lines up! cool!
            }
            int number = 0;
            sscanf(input, "%d", &number);
            setLeds(number);
            if (selection == '*'){
                setLeds(0);
                srand(number + time(0));
                setLeds(0);
                break;
            }
        }
    }

    //Shuffle deck by first arranging it in complete order, then performing swap
    Cards deck[52];
    for (int i = 1; i <= 52; i++)
        deck[i] = i;
    { //No, this isn't an accident, I really do mean to create a new scope here! I don't want to waste any more RAM than I have to!
        Cards temp = NA;
        unsigned char loc1 = 0, loc2 = 0;
        for (int i = 0; i < SHUFFLE_ROUNDS; i++) {
            loc1 = rand() % 52;
            loc2 = rand() % 52;
            temp = deck[loc1];
            deck[loc1] = deck[loc2];
            deck[loc2] = temp;
        }
    }

    Cards playerHand[11] = {NA};
    Cards mspHand[11] = {NA}; //Max hand size is 11
    //Deal two cards to each player, replacing the formerly occupied deck slots with NA (empty)
    playerHand[0] = deck[0];
    playerHand[1] = deck[1];
    mspHand[0] = deck[2];
    mspHand[1] = deck[3];
    for (int i = 0; i < 4; i++)
        deck[i] = NA;

    unsigned char deckPos = 4; //keep track of what the next card to draw is
    unsigned char playerCards = 2, mspCards = 2; //keep track of how many cards each player hsa
    char res[50] = {'0'}; //generic buffer for use with printf

    //Main game loop
    unsigned char playerBet = 0;
    unsigned char mspBet = 0;
    while (1) {

        //Display cards, get the player's bet
        CLRSCR;
        WCENTR("CARDS/BET", 15);
        sprintf(res, "PLAYER (%d): ", getHandValue(playerHand));
        WLEFT(res, 23);
        getPlayerCardString(playerHand, res, 50);
        WLEFT(res, 31);
        WLEFT("MSP:", 41);
        getMSPCardString(mspHand, res, 50);
        WLEFT(res, 49);
        WCENTR("BET (1,2,4,8)", 62);
        DRWSCR;

        mspBet += getMSPBet(mspHand);
        while (1){
            char bet = getKey();
            if (bet == '1' || bet == '2' || bet == '4' || bet == '8'){
                bet -= '0';
                setLeds(bet);
                BuzzerOn(bet + 5);
                DELAY_NOTE;
                BuzzerOff();
                playerBet += bet;
                break;
            }
        }

        CLRSCR;
        WCENTR("HIT/HOLD", 15);
        sprintf(res, "YOUR BET: %d", playerBet);
        WLEFT(res, 23);
        sprintf(res, "MSP BET: %d", mspBet);
        WLEFT(res, 31);
        WCENTR("PRESS * TO MATCH", 45);
        WCENTR("& HIT OR # TO HOLD", 53);
        DRWSCR;
        bool hold = false;
        while (1){
            char input = getKey();
            if (input != '*' && input != '#')
                continue;

            if (input == '*'){
                //Match bet and draw another card
                playerBet = (mspBet > playerBet ? mspBet : playerBet); //just in case?
                playerHand[playerCards++] = deck[deckPos++];
            }
            else
                hold = true;

            break;
        }

        //MSP will always decide whether to draw, even if the player holds. This is based solely
        //on the value of its hand.
        if (getHandValue(mspHand) < 17)
            mspHand[mspCards++] = deck[deckPos++];
        else
            hold = true;

        //End game scenarios
        //Case 1: Either player has held
        CLRSCR;
        unsigned char playerFinalVal = getHandValue(playerHand);
        unsigned char mspFinalVal = getHandValue(mspHand);
        if (hold || playerFinalVal > 21 || mspFinalVal > 21)
        {
            if (hold)
                WCENTR("GAME OVER (HOLD)", 15);
            else
                WCENTR("GAME OVER (BUST)", 15);
            if ((playerFinalVal > mspFinalVal && playerFinalVal <= 21) || mspFinalVal > 21)
                sprintf(res, "WINNER: PLR (%d)", playerBet + mspBet);
            else
                strncat(res, "WINNER: MSP (%d)", playerBet + mspBet);

            WCENTR(res, 23);
            sprintf(res, "PLAYER (%d):", playerFinalVal);
            WLEFT(res, 31);
            getPlayerCardString(playerHand, res, 50);
            WLEFT(res, 39);
            sprintf(res, "MSP (%d):", mspFinalVal);
            WLEFT(res, 49);
            getPlayerCardString(mspHand, res, 50);
            WLEFT(res, 57);
            WCENTR("* TO CONTINUE", 80);
            DRWSCR;

            while (getKey() != '*');
            break;
        }
    }

    return;
}

//Get a string that represents the hand given to it; assumes hands are NA-terminated.
static void getPlayerCardString(Cards* hand, char* buf, int n){
    memset(buf, '\0', n);
    for (int i = 0; hand[i] != NA; i++){
        strncat(buf, CardsLookup[hand[i]], n);
    }
}

//Like getPlayerCardString(), but the last two characters are XX'd
static void getMSPCardString(Cards* hand, char* buf, int n){
    getPlayerCardString(hand, buf, n);
    int length = strlen(buf);
    buf[length-1] = 'X';
    buf[length-2] = 'X';
}

//Gets the value of a player's hand. Number cards' value is defined by their number; face cards are all 11; an ace
//is interpreted optimistically, i.e. 11 if it can fit, 1 otherwise.
static unsigned char getHandValue(Cards* hand){
    unsigned char value = 0;
    //First pass: face cards/number cards
    for (int i = 0; hand[i] != NA; i++){
        Cards card = hand[i];
        if (IS_NUM(card))
            value += card % 13;
        else if (IS_FAC(card))
            value += 11;
    }

    //Second pass, aces, but optimistically
    for (int i = 0; hand[i] != NA; i++){
        if (IS_ACE(hand[i])){
            if (value <= 10)
                value += 11;
            else
                value += 1;
        }
    }

    return value;
}

//Get the MSP's bet. Do these betting rules make sense? NO IDEA!
static unsigned char getMSPBet(Cards* hand){
    unsigned char value = getHandValue(hand);
    if (value >= 18)
        return 8;
    else if (value >= 14)
        return 4;
    else if (value >= 7)
        return 2;
    return 1;
}

