// https://loj.ac/p/10181
#include <bits/stdc++.h>

using namespace std;

int n, t;
vector<int> v, dp;

bool check(int k) {
    deque<int> q;
    q.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (q.size() && q.front() < i - k - 1) q.pop_front();
        dp[i] = dp[q.front()] + v[i];
        while (q.size() && dp[q.back()] >= dp[i]) q.pop_back();
        q.push_back(i);
    }
    int res = 1e9;
    for (int i = 0; i <= k; i++) {
        res = min(res, dp[n - i]);
    }
    return res <= t;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> t;
    v.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    int l = 0, r = n;
    while (l < r) {
        int m = l + r >> 1;
        if (!check(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    cout << l << endl;
}