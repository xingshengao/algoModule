#include <bits/stdc++.h>

using namespace std;
using LL = long long;
const double PI = acos(-1);
#define all(c) c.begin(), c.end()
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
vector<PII> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
string to_string(string s) { return '"' + s + '"'; }

string to_string(const char* s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cout << endl; }

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
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };
typedef pair<int, int> PII;
vector<PII> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
static constexpr long long mod = 1e9 + 7;
using LL = long long;
class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        int g[110][110]; memset(g, 0, sizeof(g)); // g[i][j]代表修改[i: j]的开销
        auto calc = [&](int i, int j) -> int {
            int res = 0;
            for (int l = i, r = j; l < r; ++l, --r) if (s[l] != s[r]) res += 1;
            return res;
        };
        for (int i = 0; i < n; ++i) {
            g[i][i] = 0;
            for (int j = i + 1; j < n; ++j) g[i][j] = calc(i, j);
        }
        vector memo(n + 1, vector<int>(k + 1, 1e9));
        // dfs(i, j)代表s的前i个字符分成j组的子问题
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (memo[i][j] != -1) return memo[i][j];
            int &res = memo[i][j];
            if (j == 1) return res = g[0][i - 1];
            // 枚举最后一段的左端点
            for (int L = j; L <= i; ++L) {
                res = min(res, dfs(L - 1, j - 1) + g[L - 1][i - 1]);
            }
            return res;
        };
        return dfs(n, k);
    }
};
int main() {
    // Solotion so;
    return 0;
}