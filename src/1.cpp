/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <queue>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char * filename = argv[1];

    std::ifstream file(filename);
    std::string line;

    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;

    int sum = 0;

    while(std::getline(file, line)) {
        if (line.empty()) {
            queue.push(sum);
            if (queue.size() > 3) {
                queue.pop();
            }
            sum = 0;
        } else {
            sum += stoi(line);
        }
    }

    int total = 0;
    while (!queue.empty()) {
        total += queue.top();
        queue.pop();
    }

    printf("%d\n", total);

    return EXIT_SUCCESS;
}