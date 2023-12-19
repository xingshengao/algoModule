// https://www.luogu.com.cn/problem/P1169
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
    vector<vector<int>> g(n, vector<int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    // left[i][j] : 代表从(i,j)能到达的最左位置
    // right[i][j] : 代表从(i,j)能到达的最右位置
    // up[i][j] : 代表从(i,j)向上扩展最长长度

    vector<vector<int>> left(n, vector<int> (m));
    vector<vector<int>> right(n, vector<int> (m));
    vector<vector<int>> up(n, vector<int> (m, 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            left[i][j] = right[i][j] = j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (g[i][j] != g[i][j - 1]) {
                left[i][j] = left[i][j - 1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = m - 2; j >= 0; j--) {
            if (g[i][j] != g[i][j + 1]) {
                right[i][j] = right[i][j + 1];
            }
        }
    }

    int res1 = 0, res2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && g[i][j] != g[i - 1][j]) {
                left[i][j] = max(left[i][j], left[i - 1][j]);
                right[i][j] = min(right[i][j], right[i - 1][j]);
                up[i][j] = up[i - 1][j] + 1;
            }
            int x = right[i][j] - left[i][j] + 1;
            int y = min(x, up[i][j]);
            res1 = max(res1, y * y);    // 计算最大正方形
            res2 = max(res2, x * up[i][j]);   // 计算最大长方形
        }
    }
    
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}
