#include<bits/stdc++.h>
using namespace std;
// 此为三维, Leetcode1131
class Solution {
   public:
    int maxAbsValExpr(vector<int>& A, vector<int>& B) {
        int n = A.size();
        // 三维曼哈顿距离
        int d[8][3] = {{1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {-1, 1, 1}, {1, -1, -1}, {-1, -1, 1}, {-1, 1, -1}, {-1, -1, -1}};
        // 求出八个方向的最大值
        vector<int> mx(8, -1e9);
        for (int k = 0; k < 8; ++k) {
            for (int i = 0; i < n; ++i) {
                mx[k] = max(mx[k], i * d[k][0] + A[i] * d[k][1] + B[i] * d[k][2]);
            }
        }
        // 求出八个方向的最小值
        vector<int> mn(8, 1e9);
        for (int k = 0; k < 8; ++k) {
            for (int i = 0; i < n; ++i) {
                mn[k] = min(mn[k], i * d[k][0] + A[i] * d[k][1] + B[i] * d[k][2]);
            }
        }
        // 更新答案
        int ans = 0;
        for (int i = 0; i < 8; ++i) ans = max(ans, mx[i] - mn[i]);
        return ans;
    }
};