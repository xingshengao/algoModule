#include <bits/stdc++.h>
using namespace std;
typedef int long long;
using LL = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) cin >> a[i], ans += a[i];
    int x, y;
    cin >> x >> y;
    ans -= x;
    ans -= y;
    cout << ans << endl;
}

signed main() {
    solve();
    return 0;
}
