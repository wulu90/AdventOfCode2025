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

    sort(id_rangs.begin(), id_rangs.end());

    int64_t check_first = id_rangs.front().first;
    int64_t check_last  = id_rangs.front().second;
    int64_t id_count    = check_last - check_first + 1;
    for (auto [i, j] : id_rangs) {
        if (j > check_last) {
            if (i <= check_last) {
                id_count += j - check_last;
            } else {
                id_count += j - i + 1;
            }

            check_last = j;
        }
    }

    println("{}", id_count);
}

int main() {
    part1();
}
