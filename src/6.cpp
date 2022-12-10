/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <queue>

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::getline(file, line);

    std::deque<char> deque;

    for (int i = 0; i < line.size(); i++) {
        char c = line.at(i);

        std::deque<char> next_dequeue = deque;

        while (!next_dequeue.empty()) {
            char next_c = next_dequeue.front();
            next_dequeue.pop_front();

            if (next_c == c) {
                deque = next_dequeue;
                break;
            }
        }

        deque.push_back(c);

        if (deque.size() == 14) {
            printf("%d\n", i + 1);
            break;
        }
    }

    return EXIT_SUCCESS;
}