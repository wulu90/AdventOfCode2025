#include <fstream>
#include <print>
#include <vector>

using namespace std;

void part1() {
    fstream input{"input/09"};

    vector<pair<int64_t, int64_t>> red_tiles;
    while (input) {
        red_tiles.push_back({});
        input >> red_tiles.back().first;
        input.ignore();
        input >> red_tiles.back().second;
        input.ignore();
    }
    red_tiles.pop_back();    // last blank line;

    int64_t largest_rectangle_area = 0;
    for (size_t i = 0; i < red_tiles.size() - 1; ++i) {
        for (size_t j = i + 1; j < red_tiles.size(); ++j) {
            auto [xi, yi] = red_tiles[i];
            auto [xj, yj] = red_tiles[j];
            if (xi == xj && yi != yj) {
                largest_rectangle_area = max(largest_rectangle_area, abs(yi - yj) + 1);
            } else if (xi != xj && yi == yj) {
                largest_rectangle_area = max(largest_rectangle_area, abs(xi - xj) + 1);

            } else {
                largest_rectangle_area = max(largest_rectangle_area, (abs(xi - xj) + 1) * (abs(yi - yj) + 1));
            }
        }
    }

    println("{}", largest_rectangle_area);
}

int main() {
    part1();
}
