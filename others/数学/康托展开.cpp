// 例题: https://loj.ac/p/167
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int cantor(vector<int>& v) {
    int n = v.size(), mod = 998244353;
    vector<int> fact(n + 1, 1), t(n + 1), a(n);
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = v[i]; j; j -= j & -j) {
            a[i] += t[j];
        }
        for (int j = v[i]; j <= n; j += j & -j) {
            t[j]++;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = (res + a[i - 1] * fact[n - i]) % mod;
    }
    return res + 1;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    cout << cantor(v) << endl;
    return 0;
}
