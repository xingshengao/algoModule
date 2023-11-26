#include <bits/stdc++.h>
#define int long long
using namespace std;
const double PI = acos(-1);
typedef pair<int, int> PII;
typedef long long LL;
vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
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

static constexpr long long mod = 998244353;
int mypow(int x, int n) {
    int res = 1;
    for (; n; n /= 2) {
        if (n & 1) res = res * x;
        x = x * x;
    }
    return res;
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> s(m + 1);
    vector<int> b(n + 5);            // 差分数组
    vector<vector<int>> pos(m + 1);  // 存储宝石放置的位置

    for (int i = 1; i <= m; i++) cin >> s[i];  // 输入宝石的能量

    for (int i = 0; i < q; i++) {
        int p, k;
        cin >> p >> k;
        pos[p].push_back(k);
    }

    for (int i = 1; i <= m; i++) {
        if (pos[i].size() == 0) {
            continue;
        }
        sort(pos[i].begin(), pos[i].end());
        int l = pos[i][0], r = l + s[i] - 1;
        for (int j = 1; j < pos[i].size(); j++) {
            if (pos[i][j] <= r) {
                r = pos[i][j] + s[i] - 1;
            } else {
                b[l] += 1, b[min(r + 1, n + 1)] -= 1;
                l = pos[i][j], r = l + s[i] - 1;
            }
        }
        b[l] += 1, b[min(n + 1, r + 1)] -= 1;
    }

    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        cout << b[i] << " \n"[i == n];
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
