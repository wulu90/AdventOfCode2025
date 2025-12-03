#include <fstream>
#include <print>
#include <string>

using namespace std;

int find_largest_joltage_possible(const string& bank) {
    size_t first_pos = 0;
    auto first_digit = bank[0];
    for (size_t i = 1; i < bank.size() - 1; ++i) {
        if (bank[i] > first_digit) {
            first_digit = bank[i];
            first_pos   = i;
        }
    }

    auto second_pos   = first_pos + 1;
    auto second_digit = bank[second_pos];
    for (auto i = second_pos + 1; i < bank.size(); ++i) {
        if (bank[i] > second_digit) {
            second_digit = bank[i];
            second_pos   = i;
        }
    }

    return (first_digit - '0') * 10 + (second_digit - '0');
}

void part1() {
    fstream input{"input/03"};

    int res = 0;
    for (string line; getline(input, line);) {
        res += find_largest_joltage_possible(line);
    }

    println("{}", res);
}

int main() {
    part1();
}
