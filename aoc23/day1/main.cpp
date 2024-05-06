#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "include/mod_string.h"

int main () {
    std::string line;
    int sum = 0;
    int i = 0;
    // std::fstream test_file("test_input.txt");
    std::fstream test_file("input.txt");
    if (test_file.is_open()) {
        while (getline(test_file, line)) {
            int first = recover_first_int(line);
            int last = recover_last_int(line);
            int number = combine_integers(first,last);
            sum += number;
            std::cout <<"index: "<< i << "number: " << number << std::endl;
            i++;
        }
        std::cout << "The sum of all number is: " << sum << std::endl;
    }
}

int recover_first_int(std::string line) {
    for (int i = 0; i<line.length(); i++) {
        if (isdigit(line[i])) {
            char first = line[i];
            int intfirst= first - '0';
            return intfirst;
        }
    }
    return -1;
}

int recover_last_int(std::string line) {
    for (int i = line.length(); i>=0; i--) {
        if (isdigit(line[i])) {
            char last = line[i];
            int intlast = last - '0';
            return intlast;
        }
    }
    return -1;
}

int combine_integers(int first, int last) {
    return first * 10 + last;
}
