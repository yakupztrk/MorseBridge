# MorseBridge
MorseBridge is a desktop application written in C language that allows people with speech impairments to communicate with other people using the Morse code. To do this, it distinguishes short mouse clicks as dots and long mouse clicks as dashes, then converts them into readable text. This code can be adjusted for many patients' situations. Please read the [Project Report](Project%20Report_%20MorseBridge.pdf) for detailed information.

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

After doing this, compile the *MorseBridge* code using the code below:
```sh
gcc -o Project Project.c $(sdl2-config --cflags --libs)  
```
Then Run the project using the code below: 
```sh
./Project  
```

