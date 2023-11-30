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
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        map<int, int> mp;  // 存某个余数的前缀和最新出现的下标
        vector<LL> ps(n + 1);
        for (LL i = 0; i < n; ++i) ps[i + 1] = ps[i] + nums[i];
        if (ps[n] % p == 0) return 0;
        int m = ps[n] % p;
        LL ans = 1e9;
        mp[0] = -1;
        for (LL i = 0; i < n; ++i) {
            LL sum = ps[i + 1];  // [0: i]的和
            int r = sum % p;
            int target = ((r + m) % p + p) % p;
            if (i < n - 1) {
                if (mp.find(target) != mp.end()) {
                    ans = min(ans, i - mp[target] + 1);
                }
            } else if (i == n - 1) {
                if (mp.find(target) != mp.end() && mp[target] != -1) {
                    ans = min(ans, i - mp[target] + 1);
                }
            }
            mp[r] = i;
        }
        return ans == 1e9 ? -1 : ans;
    }
};
int main() {
    // Solotion so;
    return 0;
}