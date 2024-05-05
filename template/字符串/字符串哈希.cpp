// 字符串哈希题单1392. 最长快乐前缀
#include <bits/stdc++.h>
using namespace std;

// 字符串编码
class StringHash {
   public:
    static constexpr long long mod = 1e9 + 7;
    const long long base = 31;
    string s;
    long long n;
    vector<long long> preFix;                         // 编码前缀和
    vector<long long> mul;                            // 预先计算base的次幂
    long long encode(char c) { return c - 'a' + 1; }  // 字符编码函数
   public:
    StringHash() {}
    StringHash(string t) {
        s = t;
        n = s.size();
        preFix.resize(n + 1);
        mul.resize(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            preFix[i] = 0;
            mul[i] = 1;
        }
        for (int i = 0; i < s.size(); ++i) {
            preFix[i + 1] = (preFix[i] * base + encode(s[i])) % mod;
            mul[i + 1] = (mul[i] * base) % mod;
        }
    }
    // 返回s的[l, r]子串的编码
    long long get_code(long long l, long long r) { return ((preFix[r + 1] - preFix[l] * mul[r - l + 1]) % mod + mod) % mod; }
    long long get() { return get_code(0, s.size() - 1); }
};
// 使用示例
class Solution {
   public:
    int distinctEchoSubstrings(string s) {
        int n = s.size();
        StringHash string_encode(s);
        unordered_set<long long> S;
        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {                // 枚举起点
            for (int m = 1; m < (n - i) / 2 + 1; ++m) {  // 枚举一半的长度
                // 左半段 [i: i + m - 1]
                long long left = string_encode.get_code(i, i + m - 1);
                if (S.count(left)) {
                    continue;
                }
                // 右半段[i + m: i + 2 * m - 1]
                long long right = string_encode.get_code(i + m, i + 2 * m - 1);
                if (left == right) {
                    S.insert(left);
                    ans += 1;
                }
            }
        }
        return ans;
    }
};