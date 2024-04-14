#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> vec(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) cin >> vec[i];
    for (int i = 0; i < n; ++i) {
        auto s = vec[i];
        int j = 0;
        // 统计连续0是多少个
        while (j < m) {
            if (s[j] == '1') {
                ++j;
                continue;
            }
            int k = j + 1;
            int cnt = 1;
            while (k < m && s[k] == '0') {
                ++k;
                ++cnt;
            }
            j = k;
            ans += (cnt + 1) / 2;
        }
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