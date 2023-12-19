#include <bits/stdc++.h>

using namespace std;

struct RMQ {

    int n, m, lenmm;
    vector<int> mm;
    vector<vector<vector<vector<int>>>> dp;

    RMQ() {}
    // val下标从0开始
    RMQ(vector<vector<int>>& val) {
        n = val.size(), m = val[0].size();
        lenmm = max(n, m);
        mm.resize(lenmm + 1);
        mm[0] = -1;
        for (int i = 1; i <= lenmm; i++) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        }
        dp.resize(n + 1, vector<vector<vector<int>>> (m + 1, vector<vector<int>> (mm[n] + 1, vector<int> (mm[m] + 1))));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j][0][0] = val[i - 1][j - 1];
            }
        }
        for (int ii = 0; ii <= mm[n]; ii++) {
            for (int jj = 0; jj <= mm[m]; jj++) {
                if (ii + jj) {
                    for (int i = 1; i + (1 << ii) - 1 <= n; i++) {
                        for (int j = 1; j + (1 << jj) - 1 <= m; j++) {
                            if (ii) dp[i][j][ii][jj] = max(dp[i][j][ii - 1][jj], dp[i + (1 << (ii - 1))][j][ii - 1][jj]);
                            else dp[i][j][ii][jj] = max(dp[i][j][ii][jj - 1], dp[i][j + (1 << (jj - 1))][ii][jj - 1]);
                        }
                    }
                }
            }
        }
    }  
    // 下标从0开始，查询矩阵内的最大值(x1 <= x2, y1 <= y2)
    int query(int x1, int y1, int x2, int y2) {
        x1++, y1++, x2++, y2++;
        int k1 = mm[x2 - x1 + 1];
        int k2 = mm[y2 - y1 + 1];
        x2 = x2 - (1 << k1) + 1;
        y2 = y2 - (1 << k2) + 1;
        return max({dp[x1][y1][k1][k2], dp[x1][y2][k1][k2], dp[x2][y1][k1][k2], dp[x2][y2][k1][k2]});
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> val(n, vector<int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> val[i][j];

        }
    }
    RMQ R(val); 
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << R.query(x1, y1, x2, y2) << endl;
    return 0;
}
