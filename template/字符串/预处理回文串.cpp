#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void solve(string s) {
    int n = s.size();
    vector g(n + 1, vector<int>(n + 1, 0));  // g[i][j]代表预处理[i, j]是不是回文串
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (j == i)
                g[i][j] = 1;
            else
                g[i][j] = s[i] == s[j] && (j - i <= 1 || g[i + 1][j - 1]);
        }
    }
}