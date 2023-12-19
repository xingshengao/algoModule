// https://loj.ac/p/10177
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> v(n + 1), pre(n + 1), dp(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + v[i];
    }
    set<tuple<int, int>> s;
    s.insert({0, 0});
    for (int i = 1; i <= n; i++) {
        while (s.size()) {
            auto x = *s.begin();
            int a = get<0> (x), b = get<1> (x);
            if (i - b > k) s.erase(s.begin());
            else break;
        }
        auto x = *s.begin();
        int a = -get<0> (x);
        dp[i] = max(dp[i - 1], pre[i] + a);
        s.insert({-(dp[i - 1] - pre[i]), i});
    }
    cout << dp[n] << endl;
}