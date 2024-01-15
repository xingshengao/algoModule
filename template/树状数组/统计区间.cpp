#include <bits/stdc++.h>
#define int long long
using namespace std;
using LL = long long;
// 树状数组模板题目
// 小红拿到了一个数组，她想知道，有多少非空区间满足区间所有元素之和不小于

template <typename T>  // 闭区间哦
struct Fenwick {       // 使用n个需要开n-1, 即为Fenwick<int> fen(n + 1);
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
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // 转前缀和
    for (int i = 1; i < n; ++i) a[i] += a[i - 1];
    vector<LL> arr;
    arr.push_back(0);
    for (int i = 0; i < n; ++i) {
        arr.push_back(a[i]), arr.push_back(a[i] - k);
    }
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

    // 计算答案
    LL ans = 0;
    fen.add(mp[0], 1);
    for (int i = 0; i < n; ++i) {
        int y = a[i];
        int y_id = mp[y];
        int x = a[i] - k;
        int x_id = mp[x];  // 小于等于x_id的有多少个
        ans += fen.query(x_id);
        fen.add(y_id, 1);
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