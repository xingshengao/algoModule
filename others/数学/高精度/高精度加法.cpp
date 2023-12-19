// https://www.luogu.com.cn/problem/P1601
#include <bits/stdc++.h>

using namespace std;

string add(string& a, string& b) {  // 不考虑负数
    int t = 0;
    string c;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) t += a[i] - '0';
        if (i < b.size()) t += b[i] - '0';
        c += '0' + t % 10;  // 存余
        t /= 10;            // 进位
    }
    if (t) c += '0' + t;
    reverse(c.begin(), c.end());
    return c;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a, b;
    cin >> a >> b;
    cout << add(a, b) << endl;
    return 0;
}
