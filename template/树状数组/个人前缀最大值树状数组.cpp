#include <bits/stdc++.h>

using namespace std;
using LL = long long;
template <typename T>
struct Fenwick {  // 使用n个需要开n-1, 即为Fenwick<int> fen(n + 1);
    int n;
    std::vector<T> tr;

    Fenwick(int n = 0) { init(n); }
    int low_bit(int x) { return x & -x; }
    void init(int n) {
        this->n = n;
        tr.assign(n, T());
    }

    void add(int pos, T v) {
        for (; pos < tr.size(); pos += low_bit(pos)) tr[pos] += v;
    }

    T query(int pos) {
        auto res = T();
        for (; pos; pos -= low_bit(pos)) {
            res += tr[pos];
        }
        return res;
    }
    // [l, r]
    T rangeSum(int l, int r) { return query(r) - query(l - 1); }
};

// 重载MAX树状数组
struct Info {
    int x;
    Info() { x = 0; }
    Info(int val) { x = val; }
    Info operator+=(Info& rhs) {
        this->x = max(this->x, rhs.x);
        return *this;
    }
};
// 用法
int main() {
    int n = 100;
    Fenwick<Info> fen(n + 1);
    fen.add(1, Info(55));
}
