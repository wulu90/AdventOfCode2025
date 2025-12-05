#include <charconv>
#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

void part1() {
    fstream input{"input/05"};

    // read ingredient ID ranges
    vector<pair<int64_t, int64_t>> id_rangs;
    for (string line; getline(input, line) && !line.empty();) {
        id_rangs.push_back({});
        auto dash = line.find('-');
        from_chars(line.data(), line.data() + dash, id_rangs.back().first);
        from_chars(line.data() + dash + 1, line.data() + line.length(), id_rangs.back().second);
    }

    int res = 0;
    // read ingredient ID list
    for (int64_t id; input >> id;) {
        for (auto [i, j] : id_rangs) {
            if (id >= i && id <= j) {
                ++res;
                break;
            }
        }
    }

    println("{}", res);
}

int main() {
    part1();
}
