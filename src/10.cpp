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

    int cycleCount = 1;

    int strengthSum = 0;

    std::regex regex(R"((.*) (.*))");
    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, regex);

        bool isNoop = match[1] != "addx";

        int instructionCycles = isNoop ? 1 : 2;

        for (int i = 0; i < instructionCycles; i++) {
            if ((cycleCount - 20) % 40 == 0) {
                int signalStrength = cycleCount * X;
                strengthSum += signalStrength;
                printf("%d: X = %d\n", cycleCount, X);
                printf("    Signal Strength = %d\n", signalStrength);
            }
            cycleCount++;
        }

        if (cycleCount > 220) {
            break;
        }

        if (!isNoop) {
            X += std::stoi(match[2]);
        }
    }

    printf("Sum: %d\n", strengthSum);

    return EXIT_SUCCESS;
}