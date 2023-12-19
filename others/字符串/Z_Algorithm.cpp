#include <bits/stdc++.h>

using namespace std;

// 传入一个字符串s
// 返回一个vector<int> z, z[i]表示s和s[i:]的最长公共前缀的长度
// 特别地，z[0] = 0
vector<int> Z_Algorithm(string s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    string s = "aaabaab";
    vector<int> z = Z_Algorithm(s);
    for (int x : z) cout << x << ' ';
    // z = {0, 2, 1, 0, 2, 1, 0}
}