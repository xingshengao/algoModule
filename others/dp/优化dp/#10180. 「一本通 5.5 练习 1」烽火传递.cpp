// https://loj.ac/p/10180
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1), dp(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    deque<int> q;
    q.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (q.size() && q.front() < i - m) q.pop_front();
        dp[i] = dp[q.front()] + v[i];
        while (q.size() && dp[q.back()] >= dp[i]) q.pop_back();
        q.push_back(i);
    }
    int res = 1e9;
    for (int i = 0; i < m; i++) {
        res = min(res, dp[n - i]);
    }
    cout << res << endl;
}