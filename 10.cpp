#include <charconv>
#include <fstream>
#include <print>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;
using namespace std::ranges::views;

struct machine {
    vector<bool> light_diagram;
    vector<vector<size_t>> button_wiring_schematics;
    vector<int> joltage_requirements;

    machine(const string& str) {
        auto left_square_brackets  = str.find('[');
        auto right_square_brackets = str.find(']');
        for (size_t i = left_square_brackets + 1; i < right_square_brackets; ++i) {
            if (str[i] == '.') {
                light_diagram.push_back(false);
            } else {
                light_diagram.push_back(true);
            }
        }

        auto left_parenthes = right_square_brackets + 1;
        while ((left_parenthes = str.find('(', left_parenthes)) != string::npos) {
            auto right_parentheses = str.find(')', left_parenthes);

            vector<size_t> schematic = string_view{str.begin() + left_parenthes + 1, str.begin() + right_parentheses} |
                                       ranges::views::split(',') | views::transform([](auto subr) -> size_t {
                                           size_t num = 0;
                                           from_chars(subr.data(), subr.data() + subr.size(), num);
                                           return num;
                                       }) |
                                       ranges::to<vector>();
            button_wiring_schematics.push_back(schematic);
            left_parenthes = right_parentheses + 1;
        }

        auto left_curly_braces  = str.rfind('{');
        auto right_curly_braces = str.rfind('}');

        joltage_requirements = string_view{str.data() + left_curly_braces + 1, str.data() + right_curly_braces} | views::split(',') |
                               views::transform([](auto subr) -> int {
                                   int num = 0;
                                   from_chars(subr.data(), subr.data() + subr.size(), num);
                                   return num;
                               }) |
                               ranges::to<vector>();
    }
};

void solve() {
    fstream input{"input/10"};

    vector<machine> machine_vec;
    for (string line; getline(input, line);) {
        machine_vec.emplace_back(line);
    }
    /*
    for (auto m : machine_vec) {
        print("{}", m.light_diagram);
        print("{}", m.button_wiring_schematics);
        print("{}", m.joltage_requirements);
        println();
    }
    */

    size_t fewest_presses = 0;
    for (auto& machine : machine_vec) {
        vector<bool> init(machine.light_diagram.size(), false);
        queue<vector<bool>> q;
        q.push(init);

        size_t step = 0;
        while (true) {
            bool done = false;
            auto n    = q.size();
            for (size_t i = 0; i < n; ++i) {
                if (q.front() == machine.light_diagram) {
                    done = true;
                    break;
                }
                auto state = q.front();
                q.pop();

                for (auto& sch : machine.button_wiring_schematics) {
                    auto tmp = state;
                    for (auto inx : sch) {
                        tmp[inx] = !tmp[inx];
                    }
                    q.push(tmp);
                }
            }
            if (done) {
                break;
            }
            ++step;
        }
        fewest_presses += step;
    }

    println("{}", fewest_presses);
}

int main() {
    solve();
}
