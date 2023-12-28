#include <bits/stdc++.h>
#define int long long
using namespace std;
const double PI = acos(-1);
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef long long LL;
vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<pair<int, int>> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
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

// static constexpr long long mod = 998244353;
static constexpr long long mod = 1000000007;
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // 是否存在连续三个节点颜色相同, 相同输出NO
    bool ans = true;
    function<void(int, int)> dfs = [&](int x, int fa) {
        if (ans = false) return;
        if (fa == -1) {
            if (g[x].size() == 2 and s[x] == s[g[x][0]] == s[g[x][1]]) {
                ans = false;
                cout << x << endl;
            }
        } else {
            if (g[x].size() >= 2) {
                // 除父节点外, 至少有一个子节点
                vector<int> color;
                color.push_back(s[fa]);
                color.push_back(s[x]);
                for (int y : g[x]) {
                    if (y == fa) continue;
                    color.push_back(s[y]);
                }
                int a = 0, b = 0;
                for (int c : color) {
                    if (c == 0) a += 1;
                    if (c == 1) a += 2;
                }
                if (a >= 3 or b >= 3) {
                    ans = false;
                    cout << x << endl;
                    return;
                }
            }
        }
        for (int y : g[x]) {
            if (y != fa) {
                dfs(y, x);
            }
        }
    };
    dfs(0, -1);
    if (ans)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}