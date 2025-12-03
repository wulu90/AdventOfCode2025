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

    return len % 2 == 0 && id / divider == id % divider;
}

bool is_valid_part2(int64_t id) {
    int64_t tmp = id;
    int len     = 0;
    while (tmp) {
        ++len;
        tmp /= 10;
    }

    bool valid{false};
    for (int i = 1; i <= len / 2; ++i) {
        if (len % i != 0) {
            continue;
        }

        int64_t div = 1;
        for (int n = 1; n <= i; ++n) {
            div *= 10;
        }

        tmp         = id;
        int64_t seq = tmp % div;
        tmp /= div;

        bool repeat = true;
        for (int j = 1; j < len / i; ++j) {
            if (seq != tmp % div) {
                repeat = false;
                break;
            }
            tmp /= div;
        }

        if (repeat) {
            valid = true;
            break;
        }
    }

    return valid;
}

void part1() {
    ifstream input{"input/02"};

    int64_t res   = 0;
    int64_t res_2 = 0;
    for (string line; getline(input, line, ',');) {
        auto dash_pos = line.find('-');
        int64_t first, last;
        from_chars(line.data(), line.data() + dash_pos, first);
        from_chars(line.data() + dash_pos + 1, line.data() + line.length(), last);
        for (int64_t i = first; i <= last; ++i) {
            if (is_valid(i)) {
                res += i;
            }
            if (is_valid_part2(i)) {
                res_2 += i;
            }
        }
    }

    println("{}", res);
    println("{}", res_2);
}

int main() {
    part1();
}
