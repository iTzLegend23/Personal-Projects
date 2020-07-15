# README -- Minesweeper

This is a minesweeper clone written by David Waters. It is written in C++ and created in a Windows environment.
The proper suggestion is to use this on a Windows environment, but good luck to you if you wish to try and use it
in Linux or OSX. The game engine olcConsoleGameEngine.h may not like those other environments, but you are free to
try and find out. This code is available as is and is used with full knowledge as such. Absolutely no harm or any
such thing can be made out to the creator due to the use of this software. The user fully accepts and agrees to this
statement by use of this software. As such, there are bound to be bugs in the code as this software is a work in
progress and is not complete.

All code present in this repository is open source and free to use. Proper credit must go to creator(s)
and use of this code is subject to fairly and fully mentioning them in both the source code and the binaries.

minesweeper.cpp and all assets corresponding to the minesweeper clone project are property of David Waters and
subject to copyright(C). The code is free to use granted proper recognition as mentioned above.

olcConsoleGameEngine.h and olcSpriteEditor.cpp (not included here but used to create the sprites used in this
project) are property of javidx9 and subject to copyright(C) and similar recognition. Used with permission via
liscence.



### To Install:
* Download minesweeper.cpp and olcConsoleGameEngine.h
* Download the sprite assets and save them all in a folder names 'assets'
* Collect minesweeper.cpp, olcConsoleGameEngine.h and the folder containing the assests, named 'assets' into the same directory
* Compile and link the .cpp and .h files
    * Please note that the olcConsoleGameEngine.h requries the use of UNICODE character set, not the multi-byte character set
    * To use UNICODE, include the following:
        ```c++
        #ifndef UNICODE
        #define UNICODE
        #endif
        ```
* Execute the file and enjoy


### To Play:
* LMB: Reveals the current tile
* RMB: Switches a tile between flagged as a mine or removes the flag



### Current Notes:
* The game does not include a way to technically win or lose. You may uncover a tile that is a mine and the game will still play.
  Additionally, if you uncover all the tiles except the mines, the game will still go on. Exit the window to close the application.
* There is only the one size for the screen. If things are too big or too small, in the .cpp source code at the bottom change this line:
    ```
    game.ConstructConsole(256, 160, 5, 5)
    ```
* The last two lines correspond to font size (width and height), so adjusting these numbers will help in resizing the window. If it
  is too big, I recommend changing the 5's to 3's.
