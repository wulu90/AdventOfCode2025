#include <fstream>
#include <map>
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

void part2() {
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

    map<pair<size_t, size_t>, size_t> location_timelines{{{s_row, s_col}, 1}};
    for (size_t i = s_row + 1; i < diagram.size(); ++i) {
        map<pair<size_t, size_t>, size_t> tmpmap;
        for (auto [beams, t] : location_timelines) {
            auto [r, c] = beams;
            if (diagram[r + 1][c] == '.') {
                tmpmap[{r + 1, c}] += t;
            } else if (diagram[r + 1][c] == '^') {
                tmpmap[{r + 1, c - 1}] += t;
                tmpmap[{r + 1, c + 1}] += t;
            }
        }
        location_timelines = std::move(tmpmap);
    }
    size_t timelines = 0;
    for (auto [_, t] : location_timelines) {
        timelines += t;
    }
    println("{}", timelines);
}

int main() {
    part1();
    part2();
}
