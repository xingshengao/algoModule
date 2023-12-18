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
        if (!first) res += ", ";
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
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
// };
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
typedef pair<int, int> PII;
static constexpr long long mod = 1e9 + 7;
using LL = long long;
/**
 * 树上倍增算法: 预处理每个节点的第2^i个祖先节点, 任意k可分解为不同的二进制次幂, 快速到达第k个祖先节点
 * 在构造函数中, 初始化每个节点x的第2^i个祖先节点, 记作pa[x][i], 若第2^i个祖先节点不存在则pa[x][i]=-1
 * pa[x][i] = pa[pa[x][i]][i], 表示x的第2^i个祖先节点的第2^i祖先节点, 就是x的第2^(i+1)个祖先节点
 */
class TreeAncestor {
   public:
    vector<vector<int>> pa;
    TreeAncestor(int n, vector<int>& parent) { 
        init(n, parent); 
    }
    // 初始化倍增数组, n个节点, (0~n-1), fa[i]是i的父节点
    void init(int n, vector<int>& fa) {
        int m = 32 - __builtin_clz(n);  // n的二进制长度
        pa = vector<vector<int>>(n, vector<int>(m, -1));
        for (int x = 0; x < n; ++x) pa[x][0] = fa[x];
        // 先枚举i再枚举x相当于先算出所有的爷爷节点, 再算出所有的爷爷的爷爷节点
        for (int i = 0; i < m - 1; ++i) {
            for (int x = 0; x < n; ++x) {
                if (pa[x][i] != -1) {
                    pa[x][i + 1] = pa[pa[x][i]][i];
                }
            }
        }
    }
    int getKthAncestor(int node, int k) {
        int m = 32 - __builtin_clz(k);  // k的二进制长度
        for (int i = 0; i < m; ++i) {
            if ((k >> i) & 1) {
                node = pa[node][i];
                if (node < 0) break;
            }
        }
        return node;
    }
};

int main() {
    // Solotion so;
    return 0;
}