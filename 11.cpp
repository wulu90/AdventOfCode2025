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

// for part2 too slow
void recursive(const map<string_view, vector<string_view>>& matrix, vector<string_view>& path, bool dac, bool fft, size_t& count) {
    println("len {}", path.size());
    if (path.back() == "out"sv) {
        if (dac && fft) {
            ++count;
            println("{}", count);
        }
    } else {
        if (matrix.contains(path.back())) {
            for (auto& next : matrix.at(path.back())) {
                if (find(path.begin(), path.end(), next) == path.end()) {
                    path.push_back(next);
                    if (next == "dac"sv) {
                        dac = true;
                    } else if (next == "fft"sv) {
                        fft = true;
                    }
                    recursive(matrix, path, dac, fft, count);
                    path.pop_back();
                }
            }
        }
    }
}

void part2() {
    fstream input{"input/11"};

    vector<string> original_lines;

    for (string line; getline(input, line);) {
        original_lines.push_back(line);
    }

    map<string_view, vector<string_view>> matrix;
    map<string_view, vector<string_view>> pre_matrix;
    for (auto& line : original_lines) {
        auto colon = line.find(':');
        string_view lhs{line.data(), line.data() + colon};
        auto rhs = string_view{line.begin() + colon + 2, line.end()} | ranges::views::split(" "sv) |
                   ranges::views::transform([](auto subr) -> string_view { return string_view{subr}; }) | ranges::to<vector>();
        matrix.insert({lhs, rhs});
        for (auto& r : rhs) {
            pre_matrix[r].push_back(lhs);
        }
    }

    /*
     * output graphviz file
     *
    ofstream graphviz_file{"11_graphviz.dot"};
    println(graphviz_file, "digraph {{");
    for (auto& [k, vec] : matrix) {
        for (auto& v : vec) {
            println(graphviz_file, "{} -> {}", k, v);
        }
    }
    println(graphviz_file, "svr [color=red]");
    println(graphviz_file, "you [color=red]");
    println(graphviz_file, "fft [color=red]");
    println(graphviz_file, "dac [color=red]");
    println(graphviz_file, "out [color=red]");
    println(graphviz_file, "}}");
    // dot -Tpng  -o 11.png 11_graphviz.dot
    */

    // no loop in graph
    map<tuple<string_view, bool, bool>, size_t> node_count;
    node_count.insert({{"svr"sv, false, false}, 1});
    while (true) {
        map<tuple<string_view, bool, bool>, size_t> tmpmap;
        for (auto& [k, v] : node_count) {
            auto [curr, fft, dac] = k;
            if (curr == "out"sv) {
                tmpmap[k] += v;
                continue;
            }
            if (matrix.contains(curr)) {
                for (auto next : matrix[curr]) {
                    if (next == "fft"sv) {
                        tmpmap[{next, true, dac}] += v;
                    } else if (next == "dac"sv) {
                        tmpmap[{next, fft, true}] += v;
                    } else {
                        tmpmap[{next, fft, dac}] += v;
                    }
                }
            }
        }
        // println("{}", tmpmap);
        node_count   = std::move(tmpmap);
        bool all_out = true;
        for (auto& [k, v] : node_count) {
            auto [curr, fft, dac] = k;
            if (curr != "out"sv) {
                all_out = false;
                break;
            }
        }
        if (all_out) {
            break;
        }
    }
    println("{}", node_count[{"out"sv, true, true}]);
}

int main() {
    part1();
    part2();
}
