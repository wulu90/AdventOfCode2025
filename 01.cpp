#include <charconv>
#include <fstream>
#include <print>
#include <string>

using namespace std;

int main() {
    ifstream input{"input/01"};

    int dial     = 50;
    int distance = 0;
    int password = 0;
    for (string line; getline(input, line);) {
        from_chars(line.data() + 1, line.data() + line.length(), distance);
        if (line[0] == 'L') {
            dial = (dial + 100 - distance) % 100;
        } else {
            dial = (dial + distance) % 100;
        }

        if (dial == 0) {
            ++password;
        }
    }

    println("{}", password);
}
