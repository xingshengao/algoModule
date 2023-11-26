#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> s(m + 1);
    vector<int> b(n + 5);            // 差分数组
    vector<vector<int>> pos(m + 1);  // 存储宝石放置的位置

    for (int i = 1; i <= m; i++) cin >> s[i];  // 输入宝石的能量

    for (int i = 0; i < q; i++) {
        int p, k;
        cin >> p >> k;
        pos[p].push_back(k);
    }
    ////////////////////////////////////////
    for (int i = 1; i <= m; i++) {
        if (pos[i].size() == 0) {
            continue;
        }
        sort(pos[i].begin(), pos[i].end());
        int l = pos[i][0], r = l + s[i] - 1;
        for (int j = 1; j < pos[i].size(); j++) {
            if (pos[i][j] <= r) {  // 新的区间重叠的情况下, 扩展区间
                r = pos[i][j] + s[i] - 1;
            } else {  // 区间不重叠的情况下, 将原来区间的变化加上
                b[l] += 1, b[min(r + 1, n + 1)] -= 1;
                l = pos[i][j], r = l + s[i] - 1;
            }
        }
        b[l] += 1, b[min(n + 1, r + 1)] -= 1;  // 最后把最后一段的变化加上
    }
    //////////////////////////////////////
    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        cout << b[i] << " \n"[i == n];
    }
}
