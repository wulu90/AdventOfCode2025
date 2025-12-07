#include <fstream>
#include <print>
#include <set>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input{"input/07"};

    vector<string> diagram;
    for (string line; getline(input, line);) {
        diagram.push_back(line);
    }

    size_t s_row, s_col;
    for (size_t i = 0; i < diagram.size(); ++i) {
        if (diagram[i].find('S') != string::npos) {
            s_row = i;
            s_col = diagram[i].find('S');
        }
    }

    set<pair<size_t, size_t>> beams_gened{{s_row, s_col}};
    auto rownext     = s_row;
    size_t splitimes = 0;
    for (size_t i = s_row + 1; i < diagram.size(); ++i) {
        set<pair<size_t, size_t>> tmpset;
        for (auto [r, c] : beams_gened) {
            if (diagram[r + 1][c] == '.') {
                tmpset.insert({r + 1, c});
            } else if (diagram[r + 1][c] == '^') {
                tmpset.insert({r + 1, c - 1});
                tmpset.insert({r + 1, c + 1});
                ++splitimes;
            }
        }
        beams_gened = std::move(tmpset);
    }

    println("{}", splitimes);
}

int main() {
    part1();
}
