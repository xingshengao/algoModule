#include <bits/stdc++.h>
#define int long long
using namespace std;

#define all(c) c.begin(), c.end()
#define REP(i, a, b) for (int i = a; i < (b); i++)
#define RREP(i, a, b) for (int i = a; i >= b; i--)
#define print(x) cout << x << endl
using LL = long long;
using VI = vector<int>;
using VL = vector<LL>;
using VVI = vector<vector<int>>;
using VVL = vector<vector<LL>>;
using VD = vector<double>;
using VVD = vector<vector<double>>;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<LL, LL, LL>;
using VPII = vector<PII>;
using VVVI = vector<vector<vector<int>>>;
using VVVL = vector<vector<vector<LL>>>;

template <class T>
void mkuni(vector<T>& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

template <class T, class S = T>
S SUM(const vector<T>& a) {
    return accumulate(a.begin(), a.end(), S(0));
}

template <class T>
T MAX(const vector<T>& a) {
    return *max_element(a.begin(), a.end());
}

template <class T>
T MIN(const vector<T>& a) {
    return *min_element(a.begin(), a.end());
}

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)

template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

const double PI = acos(-1);
vector<pair<int, int>> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
vector<pair<int, int>> dirs4 = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

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
bool isdig(char x) { return x >= '0' && x <= '9'; }
bool isup(char x) { return x >= 'A' && x <= 'Z'; }
bool isdown(char x) { return x >= 'a' && x <= 'z'; }
bool islet(char x) { return isup(x) || isdown(x); }

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

template <typename T>
ostream& operator<<(ostream& out, const set<T>& obj) {
    out << "set(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const unordered_set<T>& obj) {
    out << "unordered_set(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const map<T1, T2>& obj) {
    out << "map(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << it->first << ": " << it->second;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const unordered_map<T1, T2>& obj) {
    out << "unordered_map(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << it->first << ": " << it->second;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& obj) {
    out << "<" << obj.first << ", " << obj.second << ">";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& obj) {
    out << "vector(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
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

static constexpr long long mod = 998244353;
// static constexpr long long mod = 1000000007;
// 塔子哥很喜欢做蛋糕，做蛋糕有k个步骤，
// 第i个步骤有ci个人可以完成，每个人只能做同时做一个蛋糕，并且只会那一个步骤，
// 也就是最多可 以同时有ci个蛋糕在进行第i个步骤。
// 一个蛋糕的第i个步骤需要tii的时间。
// 小红想要做n个蛋糕，问最少需要多少时间可以完成。

// 规划使得总时间最短
// 思路，模拟：小根堆
// 第i个步骤要想执行，必须要按顺序执行完前i−1个步骤因此对于每个蛋糕来说，
// 最先执行的一定是第1个步骤，我们可以将这n个蛋糕的初始状态存到一个小根堆中，
// 然后每次尝试去推进当前耗时最小的一个蛋糕，去执行第k+1个步骤，
// 并更新当前蛋糕所耗费的时间以及全局最大时间，如果当前蛋糕已经完成了所有步骤，
// 就将其弹出小根堆中，继续去做下一个蛋糕即可，具体可以参考代码细节以及相关注释。

void solve() {
    int n, k;
    cin >> n >> k;                        // 输入蛋糕数量和制作步骤数量
    vector<int> size(k), ti(k), wait(k);  // 初始化每个步骤的人数上限、所需时间和等待队列长度
    for (int i = 0; i < k; i++) {
        cin >> size[i] >> ti[i];  // 输入每个步骤的人数上限和所需时间
    }
    int ans = 0;                                       // 初始化完成所有蛋糕所需的最小时间
    priority_queue<PII, vector<PII>, greater<PII>> q;  // 初始化优先队列，按完成时间升序排列
    for (int i = 0; i < n; i++) {
        q.push({0, -1});  // 初始时，所有蛋糕都未开始处理
    }
    while (!q.empty()) {
        auto nw = q.top();  // 取出当前最早完成的步骤
        q.pop();
        ans = nw.first;                             // 更新完成时间
        int idx = nw.second;                        // 当前步骤索引
        if (idx != -1) {                            // 如果不是新的蛋糕开始
            if (wait[idx] > 0) {                    // 如果当前步骤有等待队列
                q.push({nw.first + ti[idx], idx});  // 添加当前步骤的下一次完成时间
                --wait[idx];                        // 等待队列长度减一
            } else {
                ++size[idx];  // 没有等待队列，当前步骤可用人数增加
            }
        }
        if (idx + 1 < k) {                          // 如果还有下一个步骤
            ++idx;                                  // 移至下一步骤
            if (size[idx] > 0) {                    // 如果下一步骤有可用人手
                --size[idx];                        // 占用一个人手
                q.push({nw.first + ti[idx], idx});  // 计划下一步骤的完成时间
            } else {
                ++wait[idx];  // 如果下一步骤没有可用人手，当前蛋糕进入等待队列
            }
        }
    }
    cout << ans << endl;  // 输出完成所有蛋糕所需的最小时间
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}