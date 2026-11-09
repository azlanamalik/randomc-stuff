#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//input we are expecting 9 10 100 (connected but not child)

auto create_hashmap(const uint64_t root) {
    std::unordered_map<uint64_t, std::vector<uint64_t>> children;
    //hashmap
    std::unordered_set<uint64_t> all{root};
    uint64_t parent {}, child {};
    while (std::cin >> parent >> child) {
        children[parent].push_back(child);
        all.insert(parent);
        all.insert(child);
    }
    return std::make_pair(children, all);
}
std::unordered_set<uint64_t> do_bfs(const std::unordered_map<uint64_t, std::vector<uint64_t>>& children, const uint64_t root) {
    // 2. BFS
    std::unordered_set<uint64_t> visited{root};
    std::queue<uint64_t> q;
    q.push(root);
    while (!q.empty()) {
        const uint64_t node = q.front();
        q.pop();//c++ way of popping read then rem
        const auto it = children.find(node);
        if (it == children.end()) continue;//LEAF skip iteration but not escape loop!!(faster)
        for (const uint64_t c : it->second)//.first is key
            if (visited.insert(c).second)//if we havent seen child then we just add it to queue
                q.push(c);
    }
    return visited;
}
int main() {
    std::ios::sync_with_stdio(false);//prevents c print stuff

    uint64_t root {};//just asssume its going to be big
    //with ceph this may be in the trillions
    if (!(std::cin >> root)) return 0;

    const auto [children, all] = create_hashmap(root);
    const std::unordered_set<uint64_t> visited = do_bfs(children, root);

    std::set<uint64_t> orphans;//create the compliment
    for (const uint64_t n : all)
        if (!visited.count(n)) orphans.insert(n);

    for (const uint64_t n : orphans) std::cout << n << '\n';
}
