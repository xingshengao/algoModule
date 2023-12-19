// https://www.luogu.com.cn/problem/P1480
#include <bits/stdc++.h>
#define int long long

using namespace std;

string div(string& a, int b) {
    int r = 0;
    string c;
    for (int i = 0; i < a.size(); i++) {
        r = r * 10 + a[i] - '0';
        c += '0' + r / b;
        r %= b;
    }
    reverse(c.begin(), c.end());
    while (c.size() > 1 && c.back() == '0') c.pop_back();
    reverse(c.begin(), c.end());
    return c;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a;
    int b;
    cin >> a >> b;
    cout << div(a, b) << endl;
    return 0;
}
