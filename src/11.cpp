/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <queue>
#include <regex>
#include <string>

int addition(int x, int y) {
    return x + y;
}

int product(int x, int y) {
    return x * y;
}

typedef int (*operatorFunction)(int, int);

std::map<char, operatorFunction> operators = {{'*', product}, {'+', addition}};

class Monkey {
   public:
    Monkey(const std::deque<int>& items, operatorFunction operation,
           std::optional<int> operationValue, int testNumber, int trueMonkey,
           int falseMonkey) {
        this->items = items;
        this->operation = operation;
        this->operationValue = operationValue;
        this->testNumber = testNumber;
        this->trueMonkey = trueMonkey;
        this->falseMonkey = falseMonkey;

        this->inspectCount = 0;
    }

    bool hasItem() {
        return !items.empty();
    }

    int inspectNextItem() {
        this->inspectCount++;
        int old = this->items.front();
        this->items.pop_front();

        int operand = operationValue.has_value() ? operationValue.value() : old;
        int newWorry = operation(old, operand);

        return floor(newWorry / 3.0);
    }

    int getReceivingMonkey(int item) {
        return item % testNumber == 0 ? trueMonkey : falseMonkey;
    }

    std::deque<int> items;
    operatorFunction operation;
    std::optional<int> operationValue;
    int testNumber;
    int trueMonkey;
    int falseMonkey;

    int inspectCount;
};

std::deque<int> splitItems(const std::string& string) {
    std::deque<int> items;
    std::stringstream ss(string);
    std::string word;
    while (std::getline(ss, word, ',')) {
        word.erase(remove(word.begin(), word.end(), ' '), word.end());
        items.push_back(std::stoi(word));
    }
    return items;
}

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::vector<Monkey> monkeys;

    std::smatch match;
    std::regex startingItemsRegex(R"(  Starting items: (.*))");
    std::regex operationRegex(R"(  Operation: new = old (.) (.*))");
    std::regex testRegex(R"(  Test: divisible by (\d*))");
    std::regex ifTrueRegex(R"(    If true: throw to monkey (\d*))");
    std::regex ifFalseRegex(R"(    If false: throw to monkey (\d*))");

    for (int monkeyCount = 0; !file.eof(); monkeyCount++) {
        // Monkey line
        std::getline(file, line);

        // Starting items
        std::getline(file, line);
        std::regex_match(line, match, startingItemsRegex);
        std::deque items = splitItems(match[1]);

        // Operation
        std::getline(file, line);
        std::regex_match(line, match, operationRegex);
        operatorFunction operation =
            operators.at(((std::string)match[1]).at(0));
        std::optional<int> operationValue = std::nullopt;
        if (match[2] != "old") {
            operationValue = std::optional<int>(std::stoi(match[2]));
        }

        // Test
        std::getline(file, line);
        std::regex_match(line, match, testRegex);
        int testNumber = std::stoi(match[1]);

        // If true
        std::getline(file, line);
        std::regex_match(line, match, ifTrueRegex);
        int trueMonkey = std::stoi(match[1]);

        // If false
        std::getline(file, line);
        std::regex_match(line, match, ifFalseRegex);
        int falseMonkey = std::stoi(match[1]);

        // Blank line
        std::getline(file, line);

        // Create new monkey
        Monkey monkey(items, operation, operationValue, testNumber, trueMonkey,
                      falseMonkey);

        monkeys.push_back(monkey);
    }

    // Inspecting 20 times
    for (int i = 0; i < 20; i++) {
        for (Monkey & monkey : monkeys) {
            while (monkey.hasItem()) {
                int item = monkey.inspectNextItem();
                int nextMonkey = monkey.getReceivingMonkey(item);
                monkeys[nextMonkey].items.push_back(item);
            }
        }
    }

    // Getting 2 max inspect counts
    std::priority_queue<int, std::vector<int>, std::greater<>> maxInspectCount;
    for (const Monkey& monkey : monkeys) {
        maxInspectCount.push(monkey.inspectCount);
        if (maxInspectCount.size() > 2) {
            maxInspectCount.pop();
        }
    }

    // Calculating monkey business
    int monkeyBusiness = maxInspectCount.top();
    maxInspectCount.pop();
    monkeyBusiness *= maxInspectCount.top();

    printf("Monkey Business: %d\n", monkeyBusiness);

    return EXIT_SUCCESS;
}