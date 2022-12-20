/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <regex>

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    int X = 1;

    int cycleCount = 0;

    std::regex regex(R"((.*) (.*))");
    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, regex);

        bool isNoop = match[1] != "addx";

        int instructionCycles = isNoop ? 1 : 2;

        for (int i = 0; i < instructionCycles; i++) {
            int xPos = cycleCount % 40;
            char pixel = xPos >= X - 1 && xPos <= X + 1 ? '#' : '.';
            printf("%c", pixel);
            cycleCount++;
            if (cycleCount % 40 == 0) {
                printf("\n");
            }
        }

        if (!isNoop) {
            X += std::stoi(match[2]);
        }
    }

    return EXIT_SUCCESS;
}