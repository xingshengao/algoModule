#include <bits/stdc++.h>
#define int long long
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

// 给定两个长度为N的排列A和B。若一对二元组下标(i,j)满足以下关系则被称之为压制二元组:
// 1<i<j ≤N。
// pAi<pAj，其中px表示值x在数组B中的下标。
// 一对压制二元组的价值被定义为j-i，请你计算出所有压制二元组的价值之和。
// 排列的定义:长度为N的排列表示一个长度为N的数组，其中[1,N]每个数都恰好出现一次。

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i], p[b[i]] = i;

    // 使用两个树状数组, 分别维护小于当前数的pos[a[i]]的个数, 和小于当前数的pos[a[i]]的和
    Fenwick<int> x(n + 1), y(n + 1);  // 逆序对模板
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += x.query(p[a[i]]) * i - y.query(p[a[i]]);
        x.add(p[a[i]], 1);
        y.add(p[a[i]], i);
    }
    cout << ans << endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}