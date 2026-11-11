// Animated fire in the terminal, drawn with coloured characters.
//
// How it works: the bottom row is always hot. Every frame each cell takes
// the heat of the cell below it, loses a random amount (cooling) and is
// shifted a little to the side (wind). Heat is then shown as a character
// and a colour.
//
// Stop with Ctrl+C. Change the settings below and compile again.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// ---------------- SETTINGS: change these and see what happens ----------------
const int WIDTH = 70;        // fire width in characters
const int HEIGHT = 24;       // fire height in lines
const int COOLING = 3;       // 1 = tall flames, 6 = low flames
const int WIND = 1;          // 0 = no wind, 1 = light, 3 = strong
const int DELAY_MS = 50;     // pause between frames; smaller = faster
const int FRAMES = 0;        // 0 = run until Ctrl+C, or a number of frames

// Characters from cold to hot. Try " .oO0@" or " 01".
const std::string CHARS = " .:^*xsS#$@";

// Colours from cold to hot (ANSI 256-colour codes).
// Blue fire: {17, 18, 19, 20, 21, 27, 33, 39, 45, 51, 231}
// Green fire: {22, 28, 34, 40, 46, 82, 118, 154, 190, 226, 231}
const std::vector<int> COLORS = {52, 88, 124, 160, 196, 202, 208, 214, 220, 226, 231};
// -----------------------------------------------------------------------------

const int MAX_HEAT = 36;

void sleepMs(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// The old Windows console needs this to understand colour codes.
void enableColors() {
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(console, &mode)) {
        SetConsoleMode(console, mode | 0x0004);
    }
#endif
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    enableColors();

    // heat[row][col]; row 0 is the top, the last row is the burning base.
    std::vector<std::vector<int>> heat(HEIGHT, std::vector<int>(WIDTH, 0));
    for (int col = 0; col < WIDTH; col++) heat[HEIGHT - 1][col] = MAX_HEAT;

    std::cout << "\033[2J\033[?25l";  // clear the screen, hide the cursor

    for (int frame = 0; FRAMES == 0 || frame < FRAMES; frame++) {
        // Spread the heat upwards.
        for (int row = 0; row < HEIGHT - 1; row++) {
            for (int col = 0; col < WIDTH; col++) {
                int shift = (WIND > 0) ? std::rand() % (WIND + 1) : 0;
                int source = col + shift;
                if (source >= WIDTH) source = WIDTH - 1;

                int value = heat[row + 1][source] - std::rand() % (COOLING + 1);
                heat[row][col] = (value > 0) ? value : 0;
            }
        }

        // Build the whole frame as one string: it flickers less than
        // printing character by character.
        std::string screen = "\033[H";  // move the cursor to the top left
        for (int row = 0; row < HEIGHT; row++) {
            for (int col = 0; col < WIDTH; col++) {
                int level = heat[row][col];
                int charIndex = level * (static_cast<int>(CHARS.size()) - 1) / MAX_HEAT;
                int colorIndex = level * (static_cast<int>(COLORS.size()) - 1) / MAX_HEAT;
                screen += "\033[38;5;" + std::to_string(COLORS[colorIndex]) + "m";
                screen += CHARS[charIndex];
            }
            screen += "\033[0m\n";
        }
        std::cout << screen << std::flush;
        sleepMs(DELAY_MS);
    }

    std::cout << "\033[?25h";  // show the cursor again
    return 0;
}
