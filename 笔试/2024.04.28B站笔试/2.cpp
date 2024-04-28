#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    string res = s.substr(k - 1);
    string t = s.substr(0, k - 1);
    if (k % 2 != n % 2) {
        res += t;
    } else {
        reverse(t.begin(), t.end());
        res += t;
    }
    cout << res << endl;
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