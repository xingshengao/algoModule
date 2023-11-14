#include <bits/stdc++.h>

using namespace std;
using LL = long long;
const double PI = acos(-1);
#define all(c) c.begin(), c.end()
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
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
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> L(n + 1, -1), R(n + 1, n);  // L, R分别存储左右两边第一个小于nums[i]的下标
        vector<int> st;
        for (int i = 0; i < n; ++i) {
            while (st.size() && nums[st.back()] >= nums[i]) st.pop_back();
            if (st.size()) L[i] = st.back();
            st.push_back(i);
        }
        st.resize(0);
        for (int i = n - 1; i >= 0; --i) {
            while (st.size() && nums[st.back()] >= nums[i]) st.pop_back();
            if (st.size()) L[i] = st.back();
            st.push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (L[i] + 1 <= k && R[i] - 1 >= k) ans = max(ans, (R[i] - L[i] - 1) * nums[i]);
        }
        return ans;
    }
};
int main() {
    // Solution so;
    return 0;
}
