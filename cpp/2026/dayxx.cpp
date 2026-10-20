#include <iostream>
#include "util/io.h"

int main() {
    std::string filename = "input/dayxx.txt";
    auto lines = readLines(filename);

    if (lines.empty()) {
        std::cerr << "Error opening the file or file is empty!" << std::endl;
        return 1;
    }

    for (const auto& line : lines) {
        // your code here
    }

    return 0;
}
