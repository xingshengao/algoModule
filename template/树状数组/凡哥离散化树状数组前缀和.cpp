#include <bits/stdc++.h>
using namespace std;
#define yn(ans) printf("%s\n", (ans) ? "Yes" : "No");
#define YN(ans) printf("%s\n", (ans) ? "YES" : "NO");
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using i64 = long long;
using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
using pii = pair<int, int>;
const int inf = 1'000'000'000;
template <class T>
bool chmax(T& a, T b) {
    if (a >= b) return false;
    a = b;
    return true;
}
template <class T>
bool chmin(T& a, T b) {
    if (a <= b) return false;
    a = b;
    return true;
}
#ifdef FAN_DEBUG
#include "debug.h"
#else
#define debug(...)
#endif
const i64 mod = 998244353;
#define MULTICASE 1
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) { init(n); }
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) { return sum(r) - sum(l); }
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};
void solve() {
    int n;
    cin >> n;
    // 方向相同
    i64 a, b;
    vector<pair<i64, i64>> pos(n);
    vector<i64> right(n);
    rep(i, 0, n) {
        cin >> a >> b;
        right[i] = b;
        pos[i] = {a, b};
    }
    sort(all(pos));
    sort(all(right), greater<i64>());
    unordered_map<i64, int> mp;
    rep(i, 0, n) mp[right[i]] = i;
    Fenwick<i64> fen(n);
    // 大于自身的有多少个
    i64 ans = 0;
    rep(i, 0, n) {
        ans += fen.sum(mp[pos[i].second]);
        fen.add(mp[pos[i].second], 1);
    }
    cout << ans << endl;
}
int main() {
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}