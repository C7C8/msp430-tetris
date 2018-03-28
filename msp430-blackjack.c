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
        deck[i] = NA;
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

    Cards playerHand[7] = {NA};
    Cards mspHand[7] = {NA}; //Max hand is 7, since 1+2+3+4+5+6=21
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

    CLRSCR;
    WCENTR("CARDS/BET", 15);

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
