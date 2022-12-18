/**
 * Benjamin Michael Taylor
 * 2022
 */

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

    int visibleCount = (2 * width) + (2 * height) - 4;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (const int* step : steps) {
                int oX = x;
                int oY = y;
                bool visible = true;
                while (oX > 0 && oX < width - 1 && oY > 0 && oY < height - 1) {
                    oX += step[0];
                    oY += step[1];
                    if (trees[oY][oX] >= trees[y][x]) {
                        visible = false;
                        break;
                    }

                }
                if (visible) {
                    visibleCount += 1;
                    break;
                }
            }
        }
    }

    printf("Visible Count: %d\n", visibleCount);

    return EXIT_SUCCESS;
}