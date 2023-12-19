#include<bits/stdc++.h>
#define int long long

using namespace std;

struct my_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    // 针对 std::pair<int, int> 作为主键类型的哈希函数
    size_t operator()(pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM) ^
            (splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

signed main() {
    unordered_map<int, int, my_hash> h;
    unordered_map<pair<int, int>, int, my_hash> pair_map;

    h[1] = 1;
    pair_map[{1, 2}] = 2;

    cout << h[1] << endl;
    cout << pair_map[{1, 2}] << endl;
}