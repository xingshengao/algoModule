#include <bits/stdc++.h>

using namespace std;

// template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
// template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
// void dbg_out() { cout << endl; }
// template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
// #define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rall(x) begin(x), end(x)
// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
using i64 = long long;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<i64, i64>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
using vpii = vector<pii>;
using vpll = vector<pll>;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 998244353; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template <class T> void mkuni(vector<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
template <class T> int lwb(vector<T>& a, const T& b) { return int(lower_bound(all(a), b) - begin(a)); }
template <class T> int upb(vector<T>& a, const T& b) { return int(upper_bound(all(a), b) - begin(a)); }
template <class T, class U> void safeErase(T& t, const U& u) { auto it = t.find(u); assert(it != end(t)); t.erase(it); }

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

#ifdef FAN_DEBUG
#include "../Util_For_Debug/template_cpp20_std.cpp"
#else
#define debug(...)
#endif

/***
 *
 *   █████▒█    ██  ▄████▄   ██ ▄█▀       ██████╗ ██╗   ██╗ ██████╗
 * ▓██   ▒ ██  ▓██▒▒██▀ ▀█   ██▄█▒        ██╔══██╗██║   ██║██╔════╝
 * ▒████ ░▓██  ▒██░▒▓█    ▄ ▓███▄░        ██████╔╝██║   ██║██║  ███╗
 * ░▓█▒  ░▓▓█  ░██░▒▓▓▄ ▄██▒▓██ █▄        ██╔══██╗██║   ██║██║   ██║
 * ░▒█░   ▒▒█████▓ ▒ ▓███▀ ░▒██▒ █▄       ██████╔╝╚██████╔╝╚██████╔╝
 *  ▒ ░   ░▒▓▒ ▒ ▒ ░ ░▒ ▒  ░▒ ▒▒ ▓▒       ╚═════╝  ╚═════╝  ╚═════╝
 *  ░     ░░▒░ ░ ░   ░  ▒   ░ ░▒ ▒░
 *  ░ ░    ░░░ ░ ░ ░        ░ ░░ ░
 *           ░     ░ ░      ░  ░
 */
#define MULTICASE 1
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= 2;
    }
    vector<int> d(n + 1);
    vector<vector<int>> ops;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        ops.push_back({l, r});
        d[l]++;
        d[r + 1]--;
    }
    for (int i = 1; i < n; i++) {
        d[i] += d[i - 1];
    }
    for (int i = 0; i < n; i++) {
        a[i] += d[i];
        a[i] %= 2;
    }
    debug(a);
    // 1. 0101...
    int t = 0;
    int left_good = -1;
    while (left_good + 1 < n && t == a[left_good + 1]) {
        left_good++;
        t ^= 1;
    }
    int right_good = n;
    t = n % 2 ? 0 : 1;
    while (right_good - 1 >= 0 && t == a[right_good - 1]) {
        right_good--;
        t ^= 1;
    }
    debug(left_good, right_good);
    if (left_good >= right_good) {
        cout << "YES" << endl;
        return;
    }
    // [left_good + 1， right_good - 1]这个区间必须满足相邻奇偶性不同
    bool ok = true;
    for (int i = left_good + 2; i <= right_good - 1; i++) {
        if (a[i] == a[i - 1]) {
            ok = false;
            break;
        }
    }
    if (ok) {
        bool ck = false;
        for (auto &op : ops) {
            if (op[0] == left_good + 1 && op[1] == right_good - 1) {
                ck = true;
                break;
            }
        }
        if (ck) {
            cout << "YES" << endl;
            return;
        }
    }
    // 2.1010 ...
    t = 1;
    left_good = -1;
    while (left_good + 1 < n && t == a[left_good + 1]) {
        left_good++;
        t ^= 1;
    }
    right_good = n;
    t = n % 2 ? 1 : 0;
    while (right_good - 1 >= 0 && t == a[right_good - 1]) {
        right_good--;
        t ^= 1;
    }
    debug(left_good, right_good);
    if (left_good >= right_good) {
        cout << "YES" << endl;
        return;
    }
    // [left_good + 1， right_good - 1]这个区间必须满足相邻奇偶性不同
    ok = true;
    for (int i = left_good + 2; i <= right_good - 1; i++) {
        if (a[i] == a[i - 1]) {
            ok = false;
            break;
        }
    }
    if (ok) {
        bool ck = false;
        for (auto &op : ops) {
            if (op[0] == left_good + 1 && op[1] == right_good - 1) {
                ck = true;
                break;
            }
        }
        if (ck) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(20);
    int T = 1;
#if MULTICASE
    cin >> T;
#endif
    while (T--) {
        solve();
    }
    return 0;
}