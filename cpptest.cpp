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
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<array<int, 3>> vec(n);
        for (int i = 0; i < n; ++i) {
            vec[i] = {startTime[i], endTime[i], profit[i]};
        }
        // 按照结束时间升序排序
        sort(vec.begin(), vec.end(), [&](auto& a, auto& b) { return a[1] < b[1]; });
        vector<int> dp(n + 1, -1);  // dp[i]表示前i个工作的最大报酬
        function<int(int)> dfs = [&](int i) -> int {
            int& res = dp[i];
            if (res != -1) return res;
            if (i == 0) return res = 0;
            int up = vec[i - 1][0];  // 第i个的开始时间
            int l = 0, r = i - 1;
            while (l < r) {
                int mid = l + (r - l + 1 >> 1);
                if (vec[mid][1] <= up)
                    l = mid;
                else
                    r = mid - 1;
            }
            res = max(dfs(i - 1), vec[i - 1][2]);
            if (vec[r][1] <= up) res = max(res, dfs(r + 1) + vec[i - 1][2]);
            return res;
        };
        for (int i = 0; i <= n; ++i) dfs(i);
        debug(dp);
        return dfs(n);
    }
};
int main() {
    // Solotion so;

    return 0;
}