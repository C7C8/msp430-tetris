#include "msp430-blackjack.h"

char* CardsLookup[] = {"  ", "CA", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CJ", "CQ", "CK", //CA instead of C10 because 1) consistency in sizing, and 2) hex.
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
        Cards temp = 0;
        unsigned char loc1 = 0, loc2 = 0;
        for (int i = 0; i < SHUFFLE_ROUNDS; i++) {
            loc1 = rand() % 52;
            loc2 = rand() % 52;
            temp = deck[loc1];
            deck[loc1] = deck[loc2];
            deck[loc2] = temp;
        }
    }

    Card playerHand[7] = {NA}, Card mspHand[7] = {NA}; //Max hand is 7, since 1+2+3+4+5+6=21
    //Deal two cards to each player, replacing the formerly occupied deck slots with NA (empty)
    playerHand[0] = deck[0];
    playerHand[1] = deck[1];
    mspHand[0] = deck[2];
    mspHand[1] = deck[3];
    for (int i = 0; i < 4; i++)
        deck[i] = NA;



    return;
}
