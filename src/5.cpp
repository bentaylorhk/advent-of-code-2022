/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <regex>

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::stack<std::string> layers;

    for (std::getline(file, line); line.find('[') != std::string::npos; std::getline(file, line)) {
        layers.push(line);
    }

    int stackCount = std::stoi(std::string(&line.back()));

    std::vector<std::stack<char>> stacks(stackCount);

    while (!layers.empty()) {
        std::string layer = layers.top();
        layers.pop();

        for (int stackNum = 0; stackNum < stackCount; stackNum++) {
            int i = (stackNum * 4) + 1;
            if (i >= layer.size()) {
                break;
            }
            char crate = layer.at(i);
            if (crate != ' ') {
                stacks[stackNum].push(crate);
            }
        }
    }

    // Blank line
    std::getline(file, line);

    std::regex regex(R"(move (\d{1,3}) from (\d{1,3}) to (\d{1,3}))");

    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, regex);

        int crateCount = std::stoi(match[1]);
        std::stack<char> * fromStack = &stacks[std::stoi(match[2])-1];
        std::stack<char> * toStack = &stacks[std::stoi(match[3])-1];

        std::stack<char> heldCrates;

        while (crateCount-- > 0) {
            heldCrates.push(fromStack->top());
            fromStack->pop();
        }

        while (!heldCrates.empty()) {
            toStack->push(heldCrates.top());
            heldCrates.pop();
        }
    }

    for (std::stack<char> stack : stacks) {
        printf("%c", stack.top());
    }
    printf("\n");

    return EXIT_SUCCESS;
}