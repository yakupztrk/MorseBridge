# MorseBridge
MorseBridge is a desktop application written in C language that allows people with speech impairments to communicate with other people using the Morse code. To do this, it distinguishes short clicks as dots and long clicks as dashes, then converts them into readable text. This code can be adjusted for many patients' situations.

## Libraries:
SDL2, stdio.h, string.h, stdbool.h, time.h

## How It Works
Short click (<200ms): .  
Long click (≥200ms): -  
Pause >600ms: end of a letter  
Pause >5s: space between words  
Outputs interpreted letters to the terminal  

## How to Compile  
I used Cygwin64 to compile this code. Before compiling the code, it is necessary to add the SDL2 library, which is required to collect mouse clicks, as a package to Cygwin64. In order for the code to run successfully, add the following packages:  
1- libSDL2-devel  
2- libSDL2_2.0_0  

![](https://photos.app.goo.gl/A9EsqpdCr99qfhtp6)


After doing this, compile the code as shown below:  
gcc -o Project Project.c $(sdl2-config --cflags --libs)  
Then run your code as follows:  
./Project  
