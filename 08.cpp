#include <algorithm>
#include <fstream>
#include <functional>
#include <limits>
#include <map>
#include <print>
#include <ranges>
#include <tuple>
#include <vector>

#ifndef NDEBUG
#include <set>
#endif

using namespace std;

void part1() {
    fstream input{"input/08"};
    vector<tuple<int64_t, int64_t, int64_t>> junction_boxes;
    while (input) {
        junction_boxes.push_back({});
        input >> get<0>(junction_boxes.back());
        input.ignore();
        input >> get<1>(junction_boxes.back());
        input.ignore();
        input >> get<2>(junction_boxes.back());
        input.ignore();
    }
    junction_boxes.pop_back();
    map<int64_t, pair<size_t, size_t>> distance_indexes;
    for (size_t i = 0; i < junction_boxes.size() - 1; ++i) {
        for (size_t j = i + 1; j < junction_boxes.size(); ++j) {
            auto [xi, yi, zi] = junction_boxes[i];
            auto [xj, yj, zj] = junction_boxes[j];
            auto dist         = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj) + (zi - zj) * (zi - zj);
            distance_indexes.insert({dist, {i, j}});
        }
    }

    vector<size_t> junction_box_group_id(junction_boxes.size(), std::numeric_limits<std::size_t>::max());

    size_t group_id_next = 0;
    for (auto [_, p] : distance_indexes | ranges::views::take(1000)) {
        auto [i, j] = p;
        if (junction_box_group_id[i] == numeric_limits<size_t>::max() && junction_box_group_id[j] == numeric_limits<size_t>::max()) {
            junction_box_group_id[i] = group_id_next;
            junction_box_group_id[j] = group_id_next;
            ++group_id_next;
        } else if (junction_box_group_id[i] != numeric_limits<size_t>::max() && junction_box_group_id[j] == numeric_limits<size_t>::max()) {
            junction_box_group_id[j] = junction_box_group_id[i];
        } else if (junction_box_group_id[i] == numeric_limits<size_t>::max() && junction_box_group_id[j] != numeric_limits<size_t>::max()) {
            junction_box_group_id[i] = junction_box_group_id[j];
        } else {
            if (junction_box_group_id[i] != junction_box_group_id[j]) {
                auto id_i = junction_box_group_id[i];
                auto id_j = junction_box_group_id[j];
                for (auto& id : junction_box_group_id) {
                    if (id == id_j) {
                        id = id_i;
                    }
                }
                /*
                for (auto& id : junction_box_group_id) {
                    if (id == id_i || id == id_j) {
                        id = group_id_next;
                    }
                }
                ++group_id_next;
                */
            }
        }
    }
#ifndef NDEBUG
    vector<set<size_t>> group_boxid(group_id_next);
    for (size_t i = 0; i < junction_boxes.size(); ++i) {
        if (junction_box_group_id[i] != numeric_limits<size_t>::max()) {
            group_boxid[junction_box_group_id[i]].insert(i);
        }
    }
    sort(group_boxid.begin(), group_boxid.end(), [](auto& lhs, auto& rhs) { return lhs.size() > rhs.size(); });
    println("{}", group_boxid);

    for (size_t i = 0; i < junction_boxes.size(); ++i) {
        size_t group_count = 0;
        for (auto& g : group_boxid) {
            if (g.contains(i)) {
                ++group_count;
            }
        }

        if (group_count > 1) {
            println("{}", i);
        }
    }
#endif
    vector<size_t> group_id_count(junction_boxes.size(), 0);
    for (auto id : junction_box_group_id) {
        if (id != numeric_limits<size_t>::max()) {
            ++group_id_count[id];
        }
    }

    sort(group_id_count.begin(), group_id_count.end(), greater<>());
    println("{}", group_id_count[0] * group_id_count[1] * group_id_count[2]);

    // part2
    for (auto& gid : junction_box_group_id) {
        gid = numeric_limits<size_t>::max();
    }
    group_id_next = 0;
    for (auto [_, p] : distance_indexes) {
        auto [i, j] = p;
        if (junction_box_group_id[i] == numeric_limits<size_t>::max() && junction_box_group_id[j] == numeric_limits<size_t>::max()) {
            junction_box_group_id[i] = group_id_next;
            junction_box_group_id[j] = group_id_next;
            ++group_id_next;
        } else if (junction_box_group_id[i] != numeric_limits<size_t>::max() && junction_box_group_id[j] == numeric_limits<size_t>::max()) {
            junction_box_group_id[j] = junction_box_group_id[i];
        } else if (junction_box_group_id[i] == numeric_limits<size_t>::max() && junction_box_group_id[j] != numeric_limits<size_t>::max()) {
            junction_box_group_id[i] = junction_box_group_id[j];
        } else {
            if (junction_box_group_id[i] != junction_box_group_id[j]) {
                auto id_i = junction_box_group_id[i];
                auto id_j = junction_box_group_id[j];
                for (auto& id : junction_box_group_id) {
                    if (id == id_j) {
                        id = id_i;
                    }
                }
            }
        }

        if (all_of(junction_box_group_id.begin(), junction_box_group_id.end(), [&](auto& p) { return p == junction_box_group_id[0]; })) {
            println("{}", get<0>(junction_boxes[i]) * get<0>(junction_boxes[j]));
            break;
        }
    }
}

int main() {
    part1();
}
