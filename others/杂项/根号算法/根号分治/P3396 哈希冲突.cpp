#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<vector<int>> sum(400, vector<int> (400));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sqrt(n); j++) {
            sum[j][i % j] += v[i];
        }
    }
    while (m--) {
        string op;
        cin >> op;
        int x, y;
        cin >> x >> y;
        if (op == "A") {
            if (x <= sqrt(n)) {
                cout << sum[x][y] << endl;
            } else {
                int res = 0;
                for (int i = y; i <= n; i += x) {
                    res += v[i];
                }
                cout << res << endl;
            }
        } else {
            for (int i = 1; i <= sqrt(n); i++) {
                sum[i][x % i] += y - v[x];
            }
            v[x] = y;
        }
    }
    return 0;
}
