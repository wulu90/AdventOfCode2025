#include <charconv>
#include <fstream>
#include <print>
#include <string>

using namespace std;

bool is_valid(int64_t id) {
    int64_t tmp = id;
    int len     = 0;
    while (tmp) {
        ++len;
        tmp /= 10;
    }
    int64_t divider = 1;
    for (int i = 0; i < len / 2; ++i) {
        divider *= 10;
    }
    if (len % 2 == 0) {
        return id / divider == id % divider;
    }
    return false;
}

void part1() {
    ifstream input{"input/02"};

    int64_t res = 0;
    for (string line; getline(input, line, ',');) {
        auto dash_pos = line.find('-');
        int64_t first, last;
        from_chars(line.data(), line.data() + dash_pos, first);
        from_chars(line.data() + dash_pos + 1, line.data() + line.length(), last);
        for (int64_t i = first; i <= last; ++i) {
            if (is_valid(i)) {
                res += i;
            }
        }
    }

    println("{}", res);
}

int main() {
    part1();
}
