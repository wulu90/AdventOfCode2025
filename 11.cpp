#include <fstream>
#include <map>
#include <print>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

void part1() {
    fstream input{"input/11"};

    vector<string> original_lines;

    for (string line; getline(input, line);) {
        original_lines.push_back(line);
    }

    map<string_view, vector<string_view>> matrix;
    for (auto& line : original_lines) {
        auto colon = line.find(':');
        string_view lhs{line.data(), line.data() + colon};
        auto rhs = string_view{line.begin() + colon + 2, line.end()} | ranges::views::split(" "sv) |
                   ranges::views::transform([](auto subr) -> string_view { return string_view{subr}; }) | ranges::to<vector>();
        matrix.insert({lhs, rhs});
    }

    queue<vector<string_view>> q;
    q.push({"you"sv});

    size_t path_count = 0;

    while (!q.empty()) {
        auto n = q.size();
        for (size_t i = 0; i < n; ++i) {
            if (q.front().back() == "out"sv) {
                ++path_count;
                q.pop();
                continue;
            }

            auto path = q.front();
            q.pop();

            auto curr = path.back();
            for (auto next : matrix[curr]) {
                if (find(path.begin(), path.end(), next) != path.end()) {
                    continue;
                }
                auto tmp = path;
                tmp.push_back(next);
                q.push(tmp);
            }
        }
    }

    println("{}", path_count);
}

int main() {
    part1();
}
