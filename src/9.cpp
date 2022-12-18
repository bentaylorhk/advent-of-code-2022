/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <math.h>

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

enum Direction { U, R, D, L };

struct Position {
    int x = 0;
    int y = 0;
};

std::vector<struct Position> offsets({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});

std::map<char, Direction> charMap{{'U', U}, {'R', R}, {'D', D}, {'L', L}};

bool isAdjacent(struct Position p1, struct Position p2) {
    return std::abs(p1.x - p2.x) <= 1 && std::abs(p1.y - p2.y) <= 1;
}

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::vector<std::vector<bool> > visited(100, std::vector<bool>(100, false));

    struct Position head, tail;

    visited[head.y][head.x] = true;

    std::regex regex(R"((.) (\d{1,3}))");

    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, regex);

        Direction d = charMap.at(line[0]);
        int moves = std::stoi(match[2]);

        struct Position offset = offsets[d];

        for (int i = 0; i < moves; i++) {
            struct Position oldHead = head;

            head.x += offset.x;
            head.y += offset.y;

            if (!isAdjacent(head, tail)) {
                tail = oldHead;
                visited[tail.y][tail.x] = true;
            }
        }
    }

    int visitedCount = 0;

    for (std::vector row : visited) {
        for (bool isVisited : row) {
            visitedCount += isVisited;
        }
    }

    printf("Tail Visited Count: %d\n", visitedCount);

    return EXIT_SUCCESS;
}