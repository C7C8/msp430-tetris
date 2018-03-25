# MSP430 Tetris

Tetris for the MSP430, a microcontroller manufactured by TI.

In order to compile, you'll need certain library files from WPI's
ECE 2049 class, which unfortunately I don't think I can provide here (sorry!)
The library depends on the ECE 2049 expansion board for the MSP430, which
provides the necessary keypad and buzzer hardware. For obvious reasons,
you'll need the Sharp 96x96 LCD too.

This project is provided more for educational purposes than it is for
practical ones, given the amount of work involved in getting this thing
to compile and run I doubt anybody will actually run this code.

Thanks to Stephen Brennan for his ncurses-based Tetris implementation,
whose Tetris implementation I used as the back end of this project.
You can find his project [here](https://github.com/brenns10/tetris).
