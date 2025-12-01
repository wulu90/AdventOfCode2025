#include <charconv>
#include <fstream>
#include <print>
#include <string>

using namespace std;

void part1() {
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

void part2() {
    ifstream input{"input/01"};

    int dial     = 50;
    int distance = 0;
    int password = 0;
    for (string line; getline(input, line);) {
        from_chars(line.data() + 1, line.data() + line.length(), distance);
        password += distance / 100;
        distance %= 100;
        // println("{},{},{}", password, distance, dial);
        if (line[0] == 'L') {
            if (dial != 0 && distance >= dial) {
                ++password;
            }

            dial = (dial + 100 - distance) % 100;
        } else {
            if (dial != 0 && distance >= (100 - dial)) {
                ++password;
            }
            dial = (dial + distance) % 100;
        }
    }
    println("{}", password);
}

int main() {
    part1();
    part2();
}
