/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <regex>

int main(int argc, char * argv[])
{
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    int sum = 0;

    std::regex regex("(\\d{1,2})-(\\d{1,2}),(\\d{1,2})-(\\d{1,2})");

    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, regex);

        int first_min = std::stoi(match[1]);
        int first_max = std::stoi(match[2]);
        int second_min = std::stoi(match[3]);
        int second_max = std::stoi(match[4]);

        int first_size = first_max - first_min;
        int second_size = second_max - second_min;
        int *larger_min, *larger_max, *smaller_min, *smaller_max;
        if (first_size > second_size) {
            larger_min = &first_min;
            larger_max = &first_max;
            smaller_min = &second_min;
            smaller_max = &second_max;
        } else {
            larger_min = &second_min;
            larger_max = &second_max;
            smaller_min = &first_min;
            smaller_max = &first_max;
        }

        if (*larger_min <= *smaller_min && *larger_max >= *smaller_max) {
            sum++;
        }
    }

    printf("%d\n", sum);
    return EXIT_SUCCESS;
}