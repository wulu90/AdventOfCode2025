#include <array>
#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

void part1() {
    fstream input{"input/04"};

    vector<string> digram;
    for (string line; getline(input, line);) {
        digram.push_back(line);
    }

    auto rownum = digram.size();
    auto colnum = digram.front().size();

    array<array<int, 2>, 8> dirs{{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};
    size_t res = 0;
    for (size_t i = 0; i < rownum; ++i) {
        for (size_t j = 0; j < colnum; ++j) {
            if (digram[i][j] != '@') {
                continue;
            }
            size_t neighbours = 0;
            for (auto [rd, cd] : dirs) {
                auto r = i + rd;
                auto c = j + cd;
                if (r < rownum && c < colnum && digram[r][c] == '@') {
                    ++neighbours;
                }
            }

            if (neighbours < 4) {
                ++res;
            }
        }
    }

    println("{}", res);
}

size_t remove_and_count(vector<string>& digram) {
    static array<array<int, 2>, 8> dirs{{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};
    auto rownum  = digram.size();
    auto colnum  = digram.front().size();
    size_t count = 0;
    for (size_t i = 0; i < rownum; ++i) {
        for (size_t j = 0; j < colnum; ++j) {
            if (digram[i][j] != '@') {
                continue;
            }
            size_t neighbours = 0;
            for (auto [rd, cd] : dirs) {
                auto r = i + rd;
                auto c = j + cd;
                if (r < rownum && c < colnum && digram[r][c] == '@') {
                    ++neighbours;
                }
            }

            if (neighbours < 4) {
                digram[i][j] = '.';
                ++count;
            }
        }
    }
    return count;
}

void part2() {
    fstream input{"input/04"};

    vector<string> digram;
    for (string line; getline(input, line);) {
        digram.push_back(line);
    }

    size_t remove_one_round = 0;
    size_t all_remove       = 0;

    do {
        remove_one_round = remove_and_count(digram);
        all_remove += remove_one_round;
    } while (remove_one_round != 0);

    println("{}", all_remove);
}

int main() {
    part1();
    part2();
}
