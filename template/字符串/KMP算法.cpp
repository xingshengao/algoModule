#include <bits/stdc++.h>
using std::string;
using std::vector;
// 使用KMP算法求出在text中, pattern出现的所有下标
std::vector<int> kmp(std::string& text, std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m);
    int c = 0;
    for (int i = 1; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        pi[i] = c;
    }

    std::vector<int> res;
    c = 0;
    for (int i = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        if (c == m) {
            res.push_back(i - m + 1);
            c = pi[c - 1];
        }
    }
    return res;
}

// 使用举例子
// 100207. 找出数组中的美丽下标 II
// 给你一个下标从 0 开始的字符串 s 、字符串 a 、字符串 b 和一个整数 k 。

// 如果下标 i 满足以下条件，则认为它是一个 美丽下标 ：

// 0 <= i <= s.length - a.length
// s[i..(i + a.length - 1)] == a
// 存在下标 j 使得：
// 0 <= j <= s.length - b.length
// s[j..(j + b.length - 1)] == b
// |j - i| <= k
// 以数组形式按 从小到大排序 返回美丽下标。
class Solution_1 {
   public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> posA = kmp(s, a);
        vector<int> posB = kmp(s, b);
        posB.push_back(-1e9), posB.push_back(1e9);
        sort(posB.begin(), posB.end());
        vector<int> ans;
        for (int i : posA) {
            auto it = upper_bound(posB.begin(), posB.end(), i);
            int x = *it;
            it--;
            int y = *it;
            if (x - i <= k or i - y <= k) ans.push_back(i);
        }
        return ans;
    }
};
