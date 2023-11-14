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
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<PII> vec;  // 存储以i为左端点的按位或的值 + 对应子数组右端点的最小值
        // 这样在遍历时ors值最大的元素对应的子数组右端点的最小值, 就是要求的最短子数组的右端点
        for (int i = n - 1; i >= 0; --i) {
            vec.emplace_back(0, i);                 // 小集合总是在后面插入的, 因此vec是递减的
            for (int j = 0; j < vec.size(); ++j) {  // 更新集合, 把nums[i]插入集合
                vec[j].first |= nums[i];
            }
            // 原地去重, 类似leetcode26题目
            int j = 0, k = 0;
            for (; j < vec.size(); ++j) {
                if (vec[k].first != vec[j].first) {  // 不重复, 先增加k
                    vec[++k] = vec[j];
                } else {  // 有重复, 只记录最小的下标, k不递增, 合并相同值, 下标取最小的
                    vec[k].second = vec[j].second;
                }
            }
            vec.resize(k + 1);  // k 是已去重的最后一个元素下标, 因此保留k+1个元素
            // 本题只用到了vec[0], 即最大的或值, 如果题目改为任意数字, 可以在vec中查找
            ans[i] = vec[0].second - i + 1;
        }
        return ans;
    }
};
int main() {
    // Solution so;
    return 0;
}
