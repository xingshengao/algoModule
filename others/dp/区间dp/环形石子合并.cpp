// https://www.luogu.com.cn/problem/P1880
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(2 * n + 1), pre(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        v[i + n] = v[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + v[i];
    }
    vector<vector<int>> midp(2 * n + 1, vector<int> (2 * n + 1, 2e9));
    vector<vector<int>> madp(2 * n + 1, vector<int> (2 * n + 1, 0));
    for (int i = 1; i <= 2 * n; i++) {
        midp[i][i] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            for (int m = l; m < r; m++) {
                midp[l][r] = min(midp[l][m] + midp[m + 1][r] + pre[r] - pre[l - 1], midp[l][r]);
                madp[l][r] = max(madp[l][m] + madp[m + 1][r] + pre[r] - pre[l - 1], madp[l][r]);
            }
        }
    }
    int mires = 2e9, mares = 0;
    for (int i = 1; i <= n; i++) {
        mires = min(mires, midp[i][i + n - 1]);
        mares = max(mares, madp[i][i + n - 1]);
    }
    cout << mires << endl;
    cout << mares << endl;
}