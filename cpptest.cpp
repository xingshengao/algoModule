#include <bits/stdc++.h>

using namespace std;
using LL = long long;
const double PI = acos(-1);
#define all(c) c.begin(), c.end()
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
vector<pair<int, int>> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
long long fpow(long long x, long long exp, long long mod) {  // 快速幂
    long long res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
long long fpow(long long x, long long exp) {  // 快速幂
    long long res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x;
        x = x * x;
    }
    return res;
}
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() {
    cout << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << " " << to_string(H);
    debug_out(T...);
}

template <typename T>
void mydebug(const char* format, T t) {
    cout << format << "=" << to_string(t) << endl;
}

template <typename Head, typename... Tail>
void mydebug(const char* format, Head H, Tail... T) {
    while (*format != ',') cout << *format++;
    cout << "=" << to_string(H) << ",";
    mydebug(format + 1, T...);
}
#define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)
// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode(int x) : val(x), next(NULL) {}
// };
// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
// };
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
typedef pair<int, int> PII;
static constexpr long long mod = 1e9 + 7;
using LL = long long;
class Solution {
   public:
    int ways(vector<string>& g, int k) {
        int m = g.size(), n = g[0].size();
        // 预处理二维前缀和
        vector s(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + (g[i][j] == 'A');
            }
        }
        // 返回[1, 2)的区域和, 左闭右开
        auto query = [&](int r1, int c1, int r2, int c2) -> int { return s[r2][c2] - s[r2][c1] - s[r1][c2] + s[r1][c1]; };
        vector dp(k + 1, vector<vector<LL>>(m + 1, vector<LL>(n + 1, -1)));
        // dfs(c, i, j)表示把左上角为ij切c到到的合法方法数量
        function<LL(LL, LL, LL)> dfs = [&](LL c, LL i, LL j) -> LL {
            if (c == 0) {
                return query(i, j, m, n) > 0 ? 1 : 0;
            }
            LL& res = dp[c][i][j];
            if (res != -1) return res;
            res = 0;
            // 枚举垂直切的位置
            for (LL j2 = j + 1; j2 < n; ++j2) {
                if (query(i, j, m, j2)) {
                    res += dfs(c - 1, i, j2);
                    res %= mod;
                }
            }
            // 枚举水平切的位置
            for (LL i2 = i + 1; i2 < m; ++i2) {
                if (query(i, j, i2, n)) {
                    res += dfs(c - 1, i2, j);
                    res %= mod;
                }
            }
            return res;
        };
        return dfs(k - 1, 0, 0);
    }
};
int main() {
    // Solotion so;
    return 0;
}