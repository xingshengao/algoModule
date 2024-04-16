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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> arr;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        arr.push_back(a[i]);
    }

    // 离散化
    auto Uni = [](vector<LL>& A) -> vector<LL> {
        vector<LL> ans(A);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };
    vector<LL> A = Uni(arr);
    map<LL, LL> mp;
    for (int i = 0; i < A.size(); ++i) {
        mp[A[i]] = i + 1;
    }

    Fenwick<LL> fen(A.size() + 1);
    Fenwick<LL> fen2(A.size() + 1);
    unordered_map<int, int> L1, L2, R1;  // 存左边比它小的数量
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        fen2.add(mp[x], 1);
        L1[x] = fen2.query(mp[x] - 1);
        L2[x] = i + 1 - fen2.query(mp[x]);
        tot += L2[x];
    }
    vector<int> ans(n, 0);

    int num = 0;
    for (int i = n - 1; i >= 0; --i) {
        num++;
        int x = a[i];
        fen.add(mp[x], 1LL);
        R1[x] = fen.query(mp[x] - 1);

    }
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        // 新增部分， 左边数字+取反数字
        ans[i] = tot + L1[x] - R1[x];
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
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