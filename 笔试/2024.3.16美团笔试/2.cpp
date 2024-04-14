#include <bits/stdc++.h>
using namespace std;
typedef int long long;
using LL = long long;

void solve() {
    int a1 = 0, a2 = 0, a3 = 0;
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (not(s[i] >= 'a' && s[i] <= 'z')) a1++;
        if (not(s[i] >= 'A' && s[i] <= 'Z')) a2++;
        if (i == 0) {
            if (not(s[i] >= 'A' && s[i] <= 'Z')) a3++;
        } else {
            if (not(s[i] >= 'a' && s[i] <= 'z')) a3++;
        }
    }
    cout << min(a1, min(a2, a3)) << endl;
}

signed main() {
    solve();
    return 0;
}
