// https://www.luogu.com.cn/problem/P3805
#include <bits/stdc++.h>

using namespace std;

string manacher(string& s) {
    string t = "$#";
    for (int i = 0; i < s.size(); i++) {
        t += s[i];
        t += '#';
    }
    int n = t.size();
    vector<int> d(n);   // d[i] 表示新串中以i为中心的最长回文串的长度的一半
    d[1] = 1;
    for (int i = 2, l, r = 1; i < n; i++) {
        if (i <= r) d[i] = min(d[r - i + l], r - i + 1);
        while (t[i - d[i]] == t[i + d[i]]) d[i]++;
        if (i + d[i] - 1 > r) l = i - d[i] + 1, r = i + d[i] - 1;
    }
    int l = 1, r = 1;
    for (int i = 1; i < n; i++) {
        if (2 * (d[i] - 1) > r - l + 1) {
            l = i - d[i] + 1;
            r = i + d[i] - 1;
        }
    }
    string res;
    for (int i = l; i <= r; i++) {
        if (t[i] != '#') res += t[i];
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    string s;
    cin >> s;
    cout << manacher(s).size() << endl;
    return 0;
}
