#include <iostream>
#include "util/io.h"

int main() {
    std::string filename = "input/day02_test.txt";
    auto lines = readLines(filename);

    if (lines.empty()) {
        std::cerr << "Error opening the file or file is empty!" << std::endl;
        return 1;
    }

    for (const auto& line : lines) {

    }

    return 0;
}