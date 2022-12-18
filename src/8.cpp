/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <math.h>

#include <fstream>
#include <iostream>
#include <vector>

const int ASCII_NUM = 48;

const int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::vector<std::vector<int>> trees;

    while (std::getline(file, line)) {
        std::vector<int> row;

        for (char c : line) {
            row.push_back(c - ASCII_NUM);
        }

        trees.push_back(row);
    }

    for (std::vector<int> row : trees) {
        for (int tree : row) {
            printf("%d", tree);
        }
        printf("\n");
    }

    int height = trees.size();
    int width = trees[0].size();

    int bestScore = 0;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int treeCount[4];
            for (int i = 0; i < 4; i++) {
                const int* step = steps[i];
                int oX = x;
                int oY = y;
                bool visible = true;
                while (oX > 0 && oX < width - 1 && oY > 0 && oY < height - 1) {
                    oX += step[0];
                    oY += step[1];
                    if (trees[oY][oX] >= trees[y][x]) {
                        treeCount[i] = std::abs((oX - x) + (oY - y));
                        visible = false;
                        break;
                    }
                    if (visible) {
                        treeCount[i] = std::abs((oX - x) + (oY - y));
                    }
                }
            }
            int score =
                treeCount[0] * treeCount[1] * treeCount[2] * treeCount[3];
            if (score > bestScore) {
                bestScore = score;
            }
        }
    }

    printf("Best Score: %d\n", bestScore);

    return EXIT_SUCCESS;
}