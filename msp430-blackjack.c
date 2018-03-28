#include "msp430-blackjack.h"

void blackjack(bool music){

    //Display welcome screen
    CLRSCR;
    WCENTR("MSP430 BLACKJACK", 15);
    WCENTR("BY C7C8", 30);
    WCENTR("PRESS * TO PLAY", 60);
    DRWSCR;
    while (getKey() != '*');
    beepStart();

    //Seed the random number generator
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
                break;
            }
        }
    }

    return;
}
