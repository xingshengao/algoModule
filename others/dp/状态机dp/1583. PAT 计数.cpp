// https://www.acwing.com/problem/content/1585/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int p = 0, a = 0, t = 0, mod = 1e9 + 7;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'P') {
            p++;
        } else if (s[i] == 'A') {
            a = (a + p) % mod;
        } else {
            t = (t + a) % mod;
        }
    }
    cout << t << endl;
}