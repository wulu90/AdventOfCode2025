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

pair<char, size_t> find_largest_joltage_with_place_remain(const string& bank, size_t place, size_t start) {
    auto digit = bank[start];
    size_t inx = start;
    for (auto i = start + 1; i <= bank.size() - place; ++i) {
        if (bank[i] > digit) {
            digit = bank[i];
            inx   = i;
        }
    }
    return {digit, inx};
}

void part2() {
    fstream input{"input/03"};

    int64_t res = 0;
    for (string line; getline(input, line);) {
        auto [c, n]     = find_largest_joltage_with_place_remain(line, 12, 0);
        int64_t largest = c - '0';
        for (size_t i = 11; i >= 1; --i) {
            auto [ci, ni] = find_largest_joltage_with_place_remain(line, i, n + 1);
            n             = ni;
            largest       = largest * 10 + (ci - '0');
        }
        res += largest;
    }
    println("{}", res);
}

int main() {
    part1();
    part2();
}
