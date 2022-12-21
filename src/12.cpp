/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <vector>

struct Coordinate {
    int x, y;
};

int main(int argc, char* argv[]) {
    std::vector<std::vector<char>> nodes;

    std::ifstream file(INPUT_FILENAME);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<char> row;
        for (char c : line) {
            if (c == 'S') {
                c = 'a';
            } else if (c == 'E') {
                c = 'z';
            }
            row.push_back(c);
        }
        nodes.push_back(row);
    }

    Coordinate current = {0, 0};

    for (auto row : nodes) {
        for (char c : row) {
            printf("%c", c);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}