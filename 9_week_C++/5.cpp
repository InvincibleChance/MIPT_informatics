#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

using namespace std;


int sumNumbersInBrackets(const string &input) {
    if (input.size() < 2 || input.front() != '[' || input.back() != ']') {
        throw invalid_argument("Invalid input string format");
    }
    string content = input.substr(1, input.size() - 2);

    if (content.empty()) {
        return 0;
    }

    stringstream ss(content);
    string token;
    int sum = 0;

    while (getline(ss, token, ',')) {
        size_t start = token.find_first_not_of(' ');
        size_t end = token.find_last_not_of(' ');
        if (start == string::npos || end == string::npos) {
            throw invalid_argument("Invalid number format");
        }
        token = token.substr(start, end - start + 1);
        try {
            sum += stoi(token);
        } catch (...) {
            throw invalid_argument("Invalid number format");
        }
    }
    return sum;
}

int main() {
    string inputs[] = {"[10, 20, 30, 40, 50]", "[4, 8, 15, 16, 23, 42]", "[20]", "[]"};
    for (const auto &input: inputs) {
        try {
            int result = sumNumbersInBrackets(input);
            cout << "Input: " << input << " -> Sum: " << result << endl;
        } catch (const invalid_argument &e) {
            cout << "Input: " << input << " -> Error: " << e.what() << endl;
        }
    }
}
