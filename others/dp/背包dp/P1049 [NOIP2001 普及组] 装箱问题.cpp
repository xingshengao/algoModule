// https://www.luogu.com.cn/problem/P1049
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int v, n;
    cin >> v >> n;
    vector<int> dp(v + 1);
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        for (int j = v; j >= 0; j--) {
            if (j - w >= 0) {
                dp[j] = max(dp[j], dp[j - w] + w);
            }
        }
    }
    cout << v - dp[v] << endl;
}