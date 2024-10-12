#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    int ans = 0;
    string s;
    for (int x : arr) {
        bool flag = false;
        s = to_string(x);
        int sum = 0;
        for (int i = 0; i < s.size(); ++i) {
            int v = s[i] - '0';
            if (v & 1) flag = true;
            sum += v;
        }
        if (flag && sum % 2 == 0) ans++;
    }
    cout << ans << endl;
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