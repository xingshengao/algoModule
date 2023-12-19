// https://www.luogu.com.cn/problem/P2142
#include <bits/stdc++.h>

using namespace std;

bool cmp(string& a, string& b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return true;
}

string sub(string& a, string& b) {  // 输入不为负数, 输出可能为负数
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string c;
    bool flag = 0;  // 标记是否为负数
    if (!cmp(a, b)) swap(a, b), flag = 1;;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t = a[i] - '0';
        if (i < b.size()) t -= b[i] - '0';
        if (t < 0) a[i + 1]--, t += 10; // 错位
        c += '0' + t;                   // 存余
    }
    while (c.size() > 1 && c.back() == '0') c.pop_back();
    if (flag) c += '-';
    reverse(c.begin(), c.end());
    return c;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a, b;
    cin >> a >> b;
    cout << sub(a, b) << endl;
    return 0;
}
