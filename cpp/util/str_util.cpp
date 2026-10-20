#include "str_util.h"
#include <sstream>
#include <string>

void splitString(std::string& input, char delimiter, std::string arr[], int& index) {
    std::istringstream stream(input);

    std::string token;

    while (std::getline(stream, token, delimiter)) {
        arr[index++] = token;
    }
}
