/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <set>

int get_priority(char item) {
    if (item > 90) {
        return item - 96;
    } else {
        return item - 38;
    }
}

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    int sum = 0;

    while (std::getline(file, line)) {
        std::set<char> items;
        int compartment_size = (int)line.size() / 2;

        for (int i = 0; i < compartment_size; i++) {
            items.insert(line.at(i));
        }

        for (int i = compartment_size; i < line.size(); i++) {
            char item = line.at(i);
            if (items.contains(item)) {
                sum += get_priority(item);
                break;
            }
        }
    }

    printf("%d\n", sum);
    return EXIT_SUCCESS;
}