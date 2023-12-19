// 模板题: https://www.luogu.com.cn/problem/P3390
// 矩阵构造方法: https://www.cnblogs.com/frog112111/archive/2013/05/19/3087648.html
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

vector<vector<int>> mat_mul(vector<vector<int>>& a, vector<vector<int>>& b) { // 给定n x p和p x m的两个矩阵a和b, 求a x b
    int n = a.size(), p = a[0].size(), m = b[0].size();
    int mod = 1e9 + 7;
    vector<vector<int>> c(n, vector<int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] = (((a[i][k] * b[k][j]) % mod + c[i][j]) % mod + mod) % mod;
            }
        }
    }
    return c;
}

vector<vector<int>> mat_pow(vector<vector<int>>& a, int b) {    // 求矩阵a的b次方
    int n = a.size();
    vector<vector<int>> res(n, vector<int> (n));
    for (int i = 0; i < n; i++) {   // 把res初始化为n阶单位矩阵
        res[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            res = mat_mul(res, a);
        }
        a = mat_mul(a, a);
        b >>= 1;
    } 
    return res;
}
signed main() {
    int n, b;
    cin >> n >> b;
    vector<vector<int>> a(n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> res = mat_pow(a, b);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}