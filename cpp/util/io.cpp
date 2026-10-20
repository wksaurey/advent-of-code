#include "util/io.h"
#include <fstream>

std::vector<std::string> readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    
    return lines;
}
