#include <bits/stdc++.h>
#define int long long
using namespace std;

using VI = vector<int>;

void solve() {
    int n, q;
    cin >> n >> q;
    VI a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    VI L(q), R(q), M(q);
    for (int i = 0; i < q; ++i) cin >> L[i];
    for (int i = 0; i < q; ++i) cin >> R[i];
    for (int i = 0; i < q; ++i) cin >> M[i];
    VI ans;

    for (int i = 0; i < q; ++i) {
        int l = L[i] - 1, r = R[i] - 1, m = M[i];
        int x = a[l];
        for (int j = l + 1; j <= r; ++j) x ^= a[j];
        int t = 0;
        for (int k = 0; k <= m; ++k) {
            t = max(t, k ^ x);
        }
        ans.push_back(t);
    }

    int res = ans[0];
    for (int i = 1; i < ans.size(); ++i) res ^= ans[i];
    cout << res << endl;
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