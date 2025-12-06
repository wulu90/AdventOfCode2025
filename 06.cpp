#include <algorithm>
#include <fstream>
#include <functional>
#include <print>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void part1() {
    fstream input{"input/06"};

    vector<vector<int64_t>> num_sheet;
    vector<char> op_vec;

    for (string line; getline(input, line);) {
        if (line.find_first_of("+*") == string::npos) {
            num_sheet.push_back({});
            istringstream iss{line};
            for (int64_t n; iss >> n;) {
                num_sheet.back().push_back(n);
            }
        } else {
            for (auto c : line) {
                if (c != ' ') {
                    op_vec.push_back(c);
                }
            }
        }
    }

    int64_t res = 0;
    for (size_t i = 0; i < num_sheet.front().size(); ++i) {
        int64_t init = op_vec[i] == '+' ? 0 : 1;
        auto func    = op_vec[i] == '+' ? static_cast<function<int64_t(int64_t, int64_t)>>(plus{})
                                        : static_cast<function<int64_t(int64_t, int64_t)>>(multiplies{});

        for (size_t j = 0; j < num_sheet.size(); ++j) {
            init = func(init, num_sheet[j][i]);
        }
        res += init;
    }

    println("{}", res);
}

void part2() {
    fstream input{"input/06"};

    vector<string> worksheet;
    for (string line; getline(input, line);) {
        worksheet.push_back(line);
    }

    int64_t res = 0;
    vector<int64_t> num_vec;
    function<int64_t(int64_t, int64_t)> func;
    bool all_space = true;

    for (size_t i = worksheet.front().size() - 1; i < worksheet.front().size(); --i) {
        all_space   = true;
        int64_t num = 0;
        for (size_t j = 0; j < worksheet.size(); ++j) {
            if (isdigit(worksheet[j][i])) {
                num       = num * 10 + (worksheet[j][i] - '0');
                all_space = false;
            } else if (worksheet[j][i] == '+') {
                func      = plus{};
                all_space = false;
            } else if (worksheet[j][i] == '*') {
                func      = multiplies<>{};
                all_space = false;
            }
        }
        if (!all_space) {
            num_vec.push_back(num);
        }

        if (all_space || i == 0) {
            res += ranges::fold_left_first(num_vec, func).value();
            num_vec.clear();
        }
    }

    println("{}", res);
}

int main() {
    part1();
    part2();
}
