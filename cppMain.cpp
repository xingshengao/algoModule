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
namespace Comb {
constexpr LL N = 1e5 + 50;
// constexpr LL mod = 1e9 + 7;
LL frac[N];  // 阶乘

void init() {
    frac[0] = frac[1] = 1;
    for (LL i = 2; i < N; ++i) frac[i] = frac[i - 1] * i % mod;
}

LL fpow(LL x, LL exp) {  // 快速幂
    LL res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

/* C(n, k) means select k from n. */
LL C(LL n, LL k) {
    LL upper = frac[n];
    LL lower = (fpow(frac[k], mod - 2) * fpow(frac[n - k], mod - 2)) % mod;  // 逆元

    return (upper * lower) % mod;
}
};  // namespace Comb
using namespace Comb;
void solve() {
    int n, m;
    cin >> n >> m;
    cout << fpow(fpow(2, m) - 1, n) % mod << endl;
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
