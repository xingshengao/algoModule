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

// string 分割
vector<string> split(typename string::const_iterator begin, typename string::const_iterator end, char val) {
    vector<string> res;
    string cur = "";
    for (auto it = begin; it != end; it++) {
        if (*it == val) {
            res.push_back(cur);
            cur.clear();
        } else
            cur.push_back(*it);
    }
    res.push_back(cur);
    return res;
}
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

// static constexpr long long mod = 998244353;
static constexpr long long mod = 1000000007;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n, 0);         // 射击总进球数
    vector<int> last(n, 0);        // 最多一次连续进球
    vector<vector<int>> down(n);   // 射击失败的顺序
    for (int i = 0; i < n; ++i) {  // i队员的所有射击情况
        int id = i;                // 队员id
        string s;
        cin >> s;
        cnt[i] = count(s.begin(), s.end(), '1');  // 总进球数量
        auto& vec = down[i];                      // 存失败的场次
        int max_len = 0;
        int cur_len = 0;
        for (int j = 0; j < m; ++j) {
            char c = s[j];
            if (c == '1') {
                cur_len++;
                max_len = max(max_len, cur_len);
            } else {
                cur_len = 0;
                vec.push_back(j);
            }
        }
        last[i] = max_len;  // 最多的一次连续进球
    }
    vector<int> id(n);
    for (int i = 0; i < n; ++i) id[i] = i;
    auto cmp = [&](const int& i, const int& j) -> bool {
        if (cnt[i] != cnt[j]) return cnt[i] > cnt[j];      // 进球总数
        if (last[i] != last[j]) return last[i] > last[j];  // 连续进球总数
        // 两人的失败进球数量是相等的
        for (int k = 0; k < down[i].size(); ++k) {
            if (down[i][k] == down[j][k])
                continue;
            else
                return down[i][k] > down[j][k];  // 失败进球越晚越好
        }
        return i < j;  //  编号越小越好
    };
    sort(id.begin(), id.end(), cmp);
    for (int i = 0; i < id.size(); ++i) {
        if (i != id.size() - 1)
            cout << id[i] + 1 << " ";
        else
            cout << id[i] + 1 << endl;
    }
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