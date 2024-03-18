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
// 求出所有区间众数之和
void solve() {
    int n;
    cin >> n;
    int ans = 0;

    // 数字不是1就是2
    // 其实思路是对的， 前缀和，1的话+1，2的话-1，对于一个前缀和s来说
    // <=s的数量说明1是众数， 反之2是众数
    // 不需要离散化，加一个偏移量即可
    const int M = 100010;
    int s = 0;
    Fenwick<LL> fen(2 * M + 4);
    fen.add(0LL + M, 1LL);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x == 1)
            s++;
        else
            s--;
        int cnt1 = fen.query(x + M);  // 1为众数的区间个数
        int cnt2 = i + 1 - fen.query(x + M);
        ans += cnt1 * 1LL + cnt2 * 2LL;
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