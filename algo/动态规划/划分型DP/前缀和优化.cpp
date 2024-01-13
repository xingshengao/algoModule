#include <bits/stdc++.h>
#define int long long
using namespace std;
// 题目 1e6个数字, 分成k段(k<=200), 使得加权区间和最大
// 考虑每个数在哪一组会使答案最大
// 状态方程转移时只需考虑前一个数应该是上一组还是与自己同组即可

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n, 0), p(k, 0);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < k; ++i) cin >> p[i];

    vector<int> s(n + 1, 0);  // 预处理前缀和
    for (int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];

    // dp[i][j]表示[0: i]分成j段的子问题
    vector dp(n + 1, vector<int>(k + 1, -1e18));

    // 只有一段直接计算
    for (int i = 0; i < n; ++i) dp[i][1] = (s[i + 1] - s[0]) * p[0];

    for (int j = 2; j <= k; ++j) {
        int tmp = dp[0][j - 1] - p[j - 1] * s[1];
        for (int i = 1; i < n; ++i) {
            dp[i][j] = tmp + p[j - 1] * s[i + 1];
            tmp = max(tmp, dp[i][j - 1] - p[j - 1] * s[i + 1]);
        }
    }

    cout << dp[n - 1][k] << std::endl;
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