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

int main() {
    part1();
}
