// https://www.luogu.com.cn/problem/P1303
#include <bits/stdc++.h>

using namespace std;

string mul(string& a, string& b) {
    int n = a.size(), m = b.size();
    string c(n + m, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int t = c[i + j] - '0' + (a[i] - '0') * (b[j] - '0');
            c[i + j + 1] += t / 10;
            c[i + j] = '0' + (t % 10);
        }
    }
    while (c.size() > 1 && c.back() == '0') c.pop_back();
    reverse(c.begin(), c.end());
    return c;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a, b;
    cin >> a >> b;
    cout << mul(a, b) << endl;
    return 0;
}
