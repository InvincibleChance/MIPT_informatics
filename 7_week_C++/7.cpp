#include <iostream>
#include <string>
#include <cctype>


void countLetters(const std::string &str, int &numLetters, int &numDigits) {
    numLetters = 0;
    numDigits = 0;
    for (char ch: str) {
        if (std::isalpha(ch)) {
            numLetters += 1;
        }
        if (std::isdigit(ch)) {
            numDigits += 1;
        }
    }
}


int main() {
    std::string strr = "Hello 123";
    int letter = 0;
    int digits = 0;
    countLetters(strr, letter, digits);
    std::cout << "Num_letter = " << letter << std::endl;
    std::cout << "Num_digits = " << digits << std::endl;
}