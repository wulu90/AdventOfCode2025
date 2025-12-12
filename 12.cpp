#include <algorithm>
#include <charconv>
#include <fstream>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

void part1() {
    ifstream input{"input/12"};

    vector<vector<string>> pattern_vec;
    vector<string> region_lines;

    for (string line; getline(input, line) && !line.empty();) {
        if (line.find('x') == string::npos) {
            vector<string> pattern;
            while (getline(input, line) && !line.empty()) {
                pattern.push_back(line);
            }
            pattern_vec.push_back(pattern);
        } else {
            region_lines.push_back(line);
        }
    }

    vector<tuple<int, int, vector<int>>> regions;

    for (string line : region_lines) {
        auto x_pos = line.find('x');
        auto colon = line.find(':');
        int w, h;
        from_chars(line.data(), line.data() + x_pos, w);
        from_chars(line.data() + x_pos + 1, line.data() + colon, h);
        auto nums = string_view{line.data() + colon + 2, line.data() + line.length()} | ranges::views::split(' ') |
                    ranges::views::transform([](auto subr) -> int {
                        int n;
                        from_chars(subr.data(), subr.data() + subr.size(), n);
                        return n;
                    }) |
                    ranges::to<vector>();
        regions.push_back({w, h, nums});
    }

    vector<int> areas;
    for (auto& p : pattern_vec) {
        int area = 0;
        for (auto& str : p) {
            area += count(str.begin(), str.end(), '#');
        }
        areas.push_back(area);
    }

    auto fit_num = count_if(regions.begin(), regions.end(), [&areas](auto& r) {
        auto v = ranges::views::zip_transform(multiplies<>(), areas, get<2>(r));
        return accumulate(v.begin(), v.end(), 0) <= (get<0>(r) * get<1>(r));
    });
    println("{}", fit_num);
}

int main() {
    part1();
}
