#include <fstream>
#include <print>
#include <ranges>
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
            auto [xi, yi]          = red_tiles[i];
            auto [xj, yj]          = red_tiles[j];
            largest_rectangle_area = max(largest_rectangle_area, (abs(xi - xj) + 1) * (abs(yi - yj) + 1));
        }
    }

    println("{}", largest_rectangle_area);

    vector<pair<int64_t, int64_t>> first_vertex{red_tiles[0]};
    int64_t largest_rg_rectangle_area = 0;
    for (size_t i = 0; i < red_tiles.size() - 1; ++i) {
        for (size_t j = i + 1; j < red_tiles.size(); ++j) {
            auto [rxmin, rxmax] = minmax(red_tiles[i].first, red_tiles[j].first);
            auto [rymin, rymax] = minmax(red_tiles[i].second, red_tiles[j].second);

            // green vertex
            bool green_line_cross = false;
            for (auto [v1, v2] : ranges::views::concat(red_tiles, first_vertex) | ranges::views::adjacent<2>) {
                auto [gxmin, gxmax] = minmax(v1.first, v2.first);
                auto [gymin, gymax] = minmax(v1.second, v2.second);

                if (rxmin < gxmax && rxmax > gxmin && rymin < gymax && rymax > gymin) {
                    green_line_cross = true;
                    break;
                }
            }

            if (!green_line_cross) {
                largest_rg_rectangle_area = max(largest_rg_rectangle_area, (rxmax - rxmin + 1) * (rymax - rymin + 1));
            }
        }
    }
    println("{}", largest_rg_rectangle_area);
}

int main() {
    part1();
}
