#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

#define Dot_Time_Limit 200 
#define Next_Letter_Time_Limit 600 

typedef struct {
    const char *input;
    char output;
} MorseMap;

MorseMap morseListesi[] = {
    {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},
    {".", 'E'}, {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'},
    {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
    {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'},
    {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
    {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
    {"-.--", 'Y'}, {"--..", 'Z'},
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
    {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
    {"---..", '8'}, {"----.", '9'}
};

char translateMorse(const char *code) {
    for (int i = 0; i < 36; i++) {
        if (strcmp(morseListesi[i].input, code) == 0) {
            return morseListesi[i].output;
        }
    }
    return '?'; 
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Morse Code Translator", 1200, 100, 640, 480, 0);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    Uint32 mouseDownMoment = 0;
    Uint32 lastUpMoment = 0;
    Uint32 mouseUpMoment = 0;
    Uint32 clickDuration = 0;
    bool mouseIsDown = false;
    bool spacePrinted = false;
    char currentMorse[10] = "";
    int morseIndex = 0;

    printf("Click the mouse to input Morse Code:\nShort click = DOT (.)\nLong click = DASH (-)\nPause to finish a letter\n");

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        mouseDownMoment = SDL_GetTicks();
                        mouseIsDown = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        mouseUpMoment = SDL_GetTicks();
                        clickDuration = mouseUpMoment - mouseDownMoment;

                        if (clickDuration < Dot_Time_Limit) {
                            currentMorse[morseIndex++] = '.';
                        } else {
                            currentMorse[morseIndex++] = '-';
                        }
                        currentMorse[morseIndex] = '\0';

                        lastUpMoment = mouseUpMoment;
                        mouseIsDown = false;
                        spacePrinted = false; // Reset on new input
                    }
                    break;
            }
        }

        if (!mouseIsDown && lastUpMoment != 0) {
            Uint32 now = SDL_GetTicks();
            Uint32 elapsed = now - lastUpMoment;

            if (elapsed > Next_Letter_Time_Limit && morseIndex > 0) {
                char letter = translateMorse(currentMorse);
                printf("%c", letter);
                fflush(stdout);
                morseIndex = 0;
                currentMorse[0] = '\0';
                spacePrinted = false; // Allow space check after this
                lastUpMoment = now;   // Reset timer to monitor for space
            }

            if (elapsed > 5000 && morseIndex == 0 && !spacePrinted) {
                printf(" ");
                fflush(stdout);
                spacePrinted = true;
            }
        }

        SDL_Delay(10);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
