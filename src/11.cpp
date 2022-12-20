/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <queue>
#include <regex>

int addition(int x, int y) {
    return x + y;
}

int product(int x, int y) {
    return x * y;
}

typedef int (*operatorFunction)(int, int);

std::map<char, operatorFunction> operators = {{'*', product}, {'+', addition}};

struct ThrowingItem {
    int receivingMonkey;
    int worry;
};

class Monkey {
   public:
    Monkey(int id, const std::deque<int>& items, operatorFunction operation,
           std::optional<int> operationValue, int testNumber, int trueMonkey,
           int falseMonkey) {
        this->id = id;
        this->items = items;
        this->operation = operation;
        this->operationValue = operationValue;
        this->testNumber = testNumber;
        this->trueMonkey = trueMonkey;
        this->falseMonkey = falseMonkey;

        this->inspectCount = 0;
    }

    [[nodiscard]] bool hasItem() const {
        return !items.empty();
    }

    int inspectNextItem() {
        inspectCount++;
        int old = items.front();
        items.pop_front();

        int operand = operationValue.has_value() ? operationValue.value() : old;
        int newWorry = operation(old, operand);

        return floor(newWorry / 3.0);
    }

    int getReceivingMonkey(int item) {
        return item % testNumber == 0 ? trueMonkey : falseMonkey;
    }

    int id;
    std::deque<int> items;
    operatorFunction operation;
    std::optional<int> operationValue;
    int testNumber;
    int trueMonkey;
    int falseMonkey;

    int inspectCount;
};

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    std::vector<Monkey> monkeys;

    for (int monkeyCount = 0; !file.eof(); monkeyCount++) {
        // get all the lines
    }

    // while (std::getline(file, line)) {
    // }
    // construct monkeys

    // instpect 20 times

    // get two biggest inspect counts

    // find monkey business level


    return EXIT_SUCCESS;
}