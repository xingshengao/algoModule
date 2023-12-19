// https://loj.ac/p/10230
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k, mod = 5000011;
    cin >> n >> k;
    vector<int> dp(n + 1), pre(n + 1);
    dp[0] = pre[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = pre[max(0, i - k - 1)];
        pre[i] = pre[i - 1] + dp[i];
        dp[i] %= mod;
        pre[i] %= mod;
    }
    cout << pre[n] << endl;
}