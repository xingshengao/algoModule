#include <bits/stdc++.h>
using namespace std;
// 预处理两个子串[i: n - 1]和[j: n - 1]最长公共后缀
void calc1(string s) {
    int n = s.size();
    vector lcp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (s[i] == s[j]) {
                lcp[i][j] = 1;
                if (i + 1 < n && j + 1 < n) lcp[i][j] += lcp[i + 1][j + 1];
            }
        }
    }
}
// 预处理两个子串[0: i]和[0: j]最长公共前缀
void calc2(string s) {
    int n = s.size();
    vector lcp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s[i] == s[j]) {
                lcp[i][j] = 1;
                if (i - 1 >= 0 && j - 1 >= 0) lcp[i][j] += lcp[i - 1][j - 1];
            }
        }
    }
}