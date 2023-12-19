// https://www.luogu.com.cn/problem/P3397
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Matrix {
    
    int n, m;
    vector<vector<int>> mat;    // 下标从0开始

    Matrix(int n, int m) {
        this->n = n;
        this->m = m;
        mat = vector<vector<int>> (n + 1, vector<int> (m + 1));
    }

    void insert(int x1, int y1, int x2, int y2, int v) {   // 差分, x1 <= x2 && y1 <= y2
        mat[x1][y1] += v;
        mat[x1][y2 + 1] -= v;
        mat[x2 + 1][y1] -= v;
        mat[x2 + 1][y2 + 1] += v;
    }

    void prefix() {     // 将mat变成二维前缀和矩阵
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                mat[i][j] += mat[i][j - 1];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                mat[i][j] += mat[i - 1][j];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) { // 查询矩阵(x1, y1)~(x2, y2)的和, x1 <= x2 && y1 <= y2
        int a = mat[x2][y2];
        int b = x1 > 0 ? mat[x1 - 1][y2] : 0;
        int c = y1 > 0 ? mat[x2][y1 - 1] : 0;
        int d = x1 > 0 && y1 > 0 ? mat[x1 - 1][y1 - 1] : 0;
        return a - b - c + d;
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    Matrix M(n + 1, n + 1);
    for (int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        M.insert(x1, y1, x2, y2, 1);
    }
    M.prefix();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << M.mat[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
