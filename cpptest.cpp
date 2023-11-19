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
    long long minIncrementOperations(vector<int>& nums, int k) {
        LL ans = 0;
        int n = nums.size();
        vector<LL> dp(n + 1, LLONG_MAX);  // dp[i]代表改变第i个数字的最小操作数量
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int delta = max(0, k - nums[i - 1]);
            // 第一种情况, 中间没有不选的
            dp[i] = min(dp[i], dp[i - 1] + delta);
            // 第二种情况, 中间有一个不选
            if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + delta);
            // 第三种情况, 中间有两个不选
            if (i >= 3) dp[i] = min(dp[i], dp[i - 3] + delta);
        }
        return min({dp[n], dp[n - 1], dp[n - 2]});
    }
};
int main() {
    // Solotion so;
    return 0;
}