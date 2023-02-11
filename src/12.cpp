/**
 * Benjamin Michael Taylor (bentaylorhk)
 * 2023
 */

#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

struct Coordinate {
    int x, y;
};

const std::vector<Coordinate> OFFSETS{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct Node {
    char height;
    int bestDistance;
};

class Grid {
   public:
    std::vector<std::vector<Node>> nodes;
    Coordinate start, end;
    std::vector<Coordinate> startingCoords;
    Grid() {
        std::ifstream file(INPUT_FILENAME);
        std::string line;
        for (int y = 0; std::getline(file, line); y++) {
            std::vector<Node> row;
            int x = 0;
            for (char c : line) {
                int bestDistance = std::numeric_limits<int>::max() - 1;
                if (c == 'S') {
                    c = 'a';
                    this->start = {x, y};
                    bestDistance = 0;
                } else if (c == 'E') {
                    c = 'z';
                    this->end = {x, y};
                }

                if (c == 'a') {
                    startingCoords.push_back({x, y});
                }

                row.push_back({c, bestDistance});
                x++;
            }
            nodes.push_back(row);
        }
    }

    size_t getHeight() {
        return nodes.size();
    }

    size_t getWidth() {
        return nodes[0].size();
    }

    Node& getNode(Coordinate coord) {
        return this->nodes[coord.y][coord.x];
    }

    std::vector<Coordinate> getValidAdjacentCoords(Coordinate coord) {
        std::vector<Coordinate> adjacentCoords = this->getAdjacentCoords(coord);

        std::vector<Coordinate> validCoords;

        char currentHeight = this->nodes[coord.y][coord.x].height;

        for (Coordinate adjacentCoord : adjacentCoords) {
            char nextHeight =
                this->nodes[adjacentCoord.y][adjacentCoord.x].height;
            if (currentHeight >= nextHeight - 1) {
                validCoords.push_back(adjacentCoord);
            }
        }

        return validCoords;
    }

    void print() {
        for (const auto& row : nodes) {
            for (Node node : row) {
                printf("%c", node.height);
            }
            printf("\n");
        }
    }

    int shortestToEnd(Coordinate initial) {
        // DFS
        std::queue<Coordinate> q;
        for (q.push(initial); !q.empty(); q.pop()) {
            auto& coord = q.front();

            int nextDistance = this->getNode(coord).bestDistance + 1;

            std::vector<Coordinate> validCoords =
                this->getValidAdjacentCoords(coord);

            for (auto adjacent : validCoords) {
                if (nextDistance < this->getNode(adjacent).bestDistance) {
                    this->getNode(adjacent).bestDistance = nextDistance;
                    q.push(adjacent);
                }
            }
        }

        return this->getNode(this->end).bestDistance;
    }

   private:
    [[nodiscard]] std::vector<Coordinate> getAdjacentCoords(Coordinate coord) {
        std::vector<Coordinate> adjacentCoords;
        for (Coordinate offset : OFFSETS) {
            int newX = coord.x + offset.x;
            int newY = coord.y + offset.y;
            if (newX >= 0 && newX < this->getWidth() && newY >= 0 &&
                newY < this->getHeight()) {
                adjacentCoords.push_back({newX, newY});
            }
        }
        return adjacentCoords;
    }
};

int main(int argc, char* argv[]) {
    Grid grid;

    // grid.print();
    int bestDistance = std::numeric_limits<int>::max();
    for (Coordinate coord : grid.startingCoords) {
        int distance = grid.shortestToEnd(coord);
        if (distance < bestDistance) {
            bestDistance = distance;
        }
    }

    printf("%d\n", grid.shortestToEnd({0, 4}));

    return EXIT_SUCCESS;
}