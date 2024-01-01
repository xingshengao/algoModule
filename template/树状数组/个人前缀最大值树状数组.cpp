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
    LL x;
    Info() { x = -1e18; }
    Info(LL val) { x = val; }
    Info operator+=(Info& rhs) {
        this->x = max(this->x, rhs.x);
        return *this;
    }
};

void LiSanHua() {  // 离散化的代码
    vector<LL> arr;
    // 要进行树状数组前缀和的点去重
    auto Uni = [](vector<LL>& A) -> vector<LL> {
        vector<LL> ans(A);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };
    // 要进行离散化的数组, 可以是x可以是y
    vector<LL> A = Uni(arr);
    // 离散化
    map<LL, LL> mp;
    for (int i = 0; i < A.size(); ++i) {
        mp[A[i]] = i + 1;
    }
    Fenwick<LL> fen(A.size() + 1);
}
// 用法
int main() {
    int n = 100;
    Fenwick<Info> fen(n + 1);
    fen.add(1, Info(55));
}
