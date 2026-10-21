#include <iostream>
#include "util/io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Missing input arg" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    auto lines = readLines(filename);

    if (lines.empty()) {
        std::cerr << "Error opening the file or file is empty!" << std::endl;
        return 1;
    }

    int distance_left;
    int location = 50;
    int reset_count = 0;

    for (const auto& line : lines) {
        char direction = line[0];
        int distance = std::stoi(line.substr(1));
        if (direction == 'R') {
            distance_left = distance;
            while (distance_left > 0) {
                location++;
                distance_left--;
                if (location % 100 == 0) {
                    reset_count++;
                    std::cout << "Landed on Zero!" << std::endl;
                }
            }
        } else if (direction == 'L') {
            distance_left = distance;
            while (distance_left > 0) {
                location--;
                distance_left--;
                if (location % 100 == 0) {
                    reset_count++;
                    std::cout << "Landed on Zero!" << std::endl;
                }
            }
        }
        std::cout << "Direction: " << direction << ", Distance: " << distance << ", Location: " << location << std::endl;
        std::cout << "Reset Count: " << reset_count << "\n\n";
    }

    std::cout << "Final Reset Count: " << reset_count << std::endl;

    return 0;
    // 5721 too low
    // 5903 wrong
}
