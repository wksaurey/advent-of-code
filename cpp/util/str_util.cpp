
#include "util/str_util.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void splitString(string& input, char delimiter, string arr[], int& index) {
    istringstream stream(input);

    string token;

    while(getline(stream, token, delimiter)) {
        arr[index++] = token;
    }
}
