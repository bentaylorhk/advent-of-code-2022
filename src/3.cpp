/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <map>
#include <set>

int get_priority(char item)
{
    if (item > 90) {
        return item - 96;
    }
    else {
        return item - 38;
    }
}

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    int sum = 0;

    std::map<char, int> items_count;

    for (int elf_count = 0; std::getline(file, line); elf_count++) {
        if (elf_count % 3 == 0 && elf_count != 0) {
            for (auto & it : items_count) {
                if (it.second == 3) {
                    sum += get_priority(it.first);
                    break;
                }
            }

            items_count.clear();
        }

        std::set<char> elf_items;

        for (char & c : line) {
            if (!elf_items.contains(c)) {
                items_count[c]++;
                elf_items.insert(c);
            }
        }
    }
    
    for (auto & it : items_count) {
        if (it.second == 3) {
            sum += get_priority(it.first);
            break;
        }
    }

    printf("%d\n", sum);
    return EXIT_SUCCESS;
}