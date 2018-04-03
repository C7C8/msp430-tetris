#pragma once
#include <msp430.h>
#include <stdlib.h>
#include "peripherals.h"
#include "common.h"

//Musical constants
#define W_NOTE 16
#define Q_NOTE 4
#define E_NOTE 2
#define S_NOTE 1
#define HZTOB(x) (32768/x) //converts Hz values into buzzer values

//Notes in Hz... I'm so sorry.
#define C0      16
#define C0S     17
#define D0      18
#define D0S     19
#define E0      20
#define F0      21
#define G0      25
#define G0S     26
#define A0      28
#define A0S     29
#define B0      31
#define C1      33
#define C1S     35
#define D1      37
#define D1S     39
#define E1      41
#define F1      44
#define F1S     46
#define G1      49
#define G1S     52
#define A1      55
#define A1S     58
#define B1      62
#define C2      65
#define C2S     69
#define D2      73
#define D2S     78
#define E2      82
#define F2      87
#define F2S     93
#define G2      98
#define G2S     104
#define A2      110
#define A2S     117
#define B2      123
#define C3      131
#define C3S     139
#define D3      147
#define D3S     156
#define E3      165
#define F3      175
#define F3S     185
#define G3      196
#define G3S     207
#define A3      220
#define A3S     233
#define B3      247
#define C4      262 //LET'S HAVE A BLAST
#define C4S     277
#define D4      294
#define D4S     311
#define E4      329
#define F4      349
#define F4S     370
#define G4      392
#define G4S     415
#define A4      440
#define A4S     466
#define B4      494
#define C5      523
#define C5S     554
#define D5      587
#define D5S     622
#define E5      659
#define F5      698
#define F5S     740
#define G5      784
#define G5S     831
#define A5      880
#define A5S     932
#define B5      988
#define C6      1047
#define C6S     1109
#define D6      1175
#define D6S     1245
#define E6      1319
#define F6      1397
#define F6S     1480
#define G6      1568
#define G6S     1661
#define A6      1760
#define A6S     1865
#define B6      1976
#define C7      2093
#define C7S     2217
#define D7      2349
#define D7S     2489
#define E7      2637
#define F7      2794
#define F7S     2960
#define G7      3136
#define G7S     3322
#define A7      3520
#define A7S     3729
#define B7      3951
#define C8      4186
#define C8S     4435
#define D8      4699
#define D8S     4978
#define E8      5274
#define F8      5588
#define F8S     5920
#define G8      6272
#define G8S     6645
#define A8      7040
#define A8S     7459
#define B8      7902
#define NONE    32770

typedef struct {
    unsigned int note;
    unsigned char length;
} Note;

void configMusic();
void playMusic(Note* music, unsigned int length, unsigned int bpm);
void stopMusic();

//Songs
#define TETRIS_NOTE_COUNT 88
#define TETRIS_SPEED 6
extern Note tetrisTheme[TETRIS_NOTE_COUNT];

#define STARWARS_NOTE_COUNT 74
#define STARWARS_SPEED 100
extern Note starWarsTheme[STARWARS_NOTE_COUNT];
