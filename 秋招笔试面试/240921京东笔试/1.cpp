#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    // 求最少分组数量
    int i = 0;
    int ans = 0;
    while (i < n) {
        int j = i;
        int mn = a[i], mx = a[i];
        while (j < n && mx - mn <= k) {
            j++;
            mx = max(mx, a[j]);
            mn = min(mn, a[j]);
        }
        ans ++;
        i = j;
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