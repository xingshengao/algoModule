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

class _Solution {  // 二维前缀和 + 哈希表, 求矩阵中区域和为target的数量
   public:
    int numSubmatrixSumTarget(vector<vector<int>>& g, int target) {
        int m = g.size(), n = g[0].size();
        vector s(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + g[i][j];
            }
        }
        // 返回[1, 2)的区域和, 左闭右开
        auto query = [&](int r1, int c1, int r2, int c2) -> int { return s[r2][c2] - s[r2][c1] - s[r1][c2] + s[r1][c1]; };

        int ans = 0;

        for (int high = 0; high < m; ++high) {
            for (int low = high; low < m; ++low) {
                int cur = 0;
                // 上下边界确定的情况下, 找左右边界
                unordered_map<int, int> mp;
                for (int r = 0; r < n; ++r) {
                    // 上界为high, 下界为low, 左边界为0, 右边界weir的区域和
                    cur = s[low + 1][r + 1] - s[high][r + 1];
                    if (cur == target) ans++;
                    if (mp.find(cur - target) != mp.end()) ans += mp[cur - target];
                    mp[cur]++;
                }
            }
        }
        return ans;
    }
};