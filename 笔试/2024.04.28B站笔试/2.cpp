#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    if (n % 2 == 0) {
        string ans = s.substr(k - 1);
        string t = s.substr(0, k - 1);
        // cout << ans << endl;
        // cout << t << endl;
        string res = ans;
        if (k % 2 == 1) {
            res += t;
        } else {
            reverse(t.begin(), t.end());
            res += t;
        }
        cout << res << endl;
    } else {
        string ans = s.substr(k - 1);
        string t = s.substr(0, k - 1);
        // cout << ans << endl;
        // cout << t << endl;
        string res = ans;
        if (k % 2 == 0) {
            res += t;
        } else {
            reverse(t.begin(), t.end());
            res += t;
        }
        cout << res << endl;
    }
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}