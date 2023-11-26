#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n, k, l;
    cin >> n >> k >> l;
    vector d(l + 10, vector<int>(l + 10, 0));  // 二维差分数组
    int x, y;
    ///////////////////////////////////////////////////////////////////
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        d[x][y]++;
        d[x + k][y]--;
        d[x][y + k]--;
        d[x + k][y + k]++;
    }
    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= l; ++j) {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];  // 二维前缀和
        }
    }
    /////////////////////////////////////////////////////////////////////
    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= l; ++j) {
            d[i][j] = d[i][j - 1] + (d[i][j] >= 1);  // 二维转一维
        }
    }
    int q;
    cin >> q;
    while (q--) {
        cin >> x >> y;
        int ans = 0;
        for (int i = x; i < x + k; ++i) {
            ans += k - (d[i][y + k - 1] - d[i][y - 1]);
        }
        cout << ans << endl;
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
