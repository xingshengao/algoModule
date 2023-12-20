#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class Solution {
   public:
    void f(vector<vector<int>>& g) {
        // 预处理二维前缀和
        int m = g.size(), n = g[0].size();
        vector s(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + (g[i][j]);
            }
        }
        // 返回[1, 2)的区域和, 左闭右开
        auto query = [&](int r1, int c1, int r2, int c2) -> int { return s[r2][c2] - s[r2][c1] - s[r1][c2] + s[r1][c1]; };
    }
};