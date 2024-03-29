#include <bits/stdc++.h>
#define int long long
using namespace std;
using PII = pair<int, int>;
bool is(int n) { return (n % 2 + 2) % 2 == 0; }
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int sum = accumulate(a.begin(), a.end(), 0LL);
    // 选择全是偶数的子数组的最小和

    // 分组循环，选出全是偶数的区间
    vector<PII> vec;  // 存闭区间
    int i = 0;
    while (i < n) {
        if (!is(a[i])) {
            ++i;
            continue;
        }
        int j = i + 1;
        while (j < n && is(a[j])) ++j;
        vec.push_back(PII(i, j - 1));
        i = j;
    }
    // debug(vec);
    // 计算区间内的最小和
    auto calc = [&](int i, int j) -> int {
        int res = a[i];
        int s = 0;
        for (int k = i; k <= j; ++k) {
            if (s > 0) s = 0;
            s += a[k];
            res = min(res, s);
        }
        return res;
    };
    // 没有偶数区间
    if (vec.size() == 0) {
        cout << sum << endl;
        return;
    }
    int mn = 1e18;
    for (auto& [l, r] : vec) {
        mn = min(mn, calc(l, r));
    }
    if (mn > 0) {
        // 偶数区间都是正数，操作没必要
        cout << sum << endl;
        return;
    }
    cout << sum + (-mn) / 2 << endl;
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