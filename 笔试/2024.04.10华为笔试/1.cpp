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
// static constexpr long long mod = 998244353;
static constexpr long long mod = 1000000007;
// 编写一个程序为某云服务计算客户话单，输入为某云服务的计费日志和各种计费因子的计费单价的列表，
// 计费日志内容包含时间戳、客户标识、计费因子、计费时长4个字段。
// 日志中如果同一客户同一计费因子在相同时间戳上报多次话单只能计费一次，
// 选先上报的日志计费。计算每个客户的话单总费用。
void solve() {
    int n;
    cin >> n;  // 日志条数
    map<pair<int, string>, set<string>> time_core_to_user;
    map<string, vector<pair<string, int>>> user_to_core_last;
    for (int i = 0; i < n; ++i) {
        int time;     // 时间戳
        string user;  // 客户标识
        string core;  // 计费因子
        int last;     // 计费时长，0-100
        string s;
        cin >> s;
        auto vec = split(s.begin(), s.end(), ',');
        time = stoi(vec[0]);
        user = vec[1];
        core = vec[2];
        last = stoi(vec[3]);
        if (last > 100) last = 0;
        if (!time_core_to_user.count(make_pair(time, core)) || !time_core_to_user[make_pair(time, core)].count(user)) {
            time_core_to_user[make_pair(time, core)].insert(user);
            user_to_core_last[user].push_back(make_pair(core, last));
        }
    }
    int m;
    cin >> m;  // 记费因子数量
    map<string, int> core_to_cost;
    for (int i = 0; i < m; ++i) {
        string s;
        string core;
        int a;
        cin >> s;
        auto vec = split(s.begin(), s.end(), ',');
        core = vec[0];
        a = stoi(vec[1]);
        core_to_cost[core] = a;
    }
    map<string, int> ans;
    for (auto& [user, vec] : user_to_core_last) {
        int sum = 0;
        for (auto& [core, last] : vec) {
            sum += core_to_cost[core] * last;
        }
        ans[user] = sum;
    }
    for (auto& [user, sum] : ans) {
        cout << user << "," << sum << endl;
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