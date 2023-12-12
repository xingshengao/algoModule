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
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    set<int> S(a.begin(), a.end());
    if (S.size() == n) {
        cout << -1 << endl;
        return;
    }
    vector<vector<int>> ans;
    int i = 0;
    S.clear();
    while (i < n) {
        S.clear();
        int j = i;
        while (j < n && S.size() == j - i) {
            S.insert(a[j]);
            j++;
        }
        //[i : j - 1]
        ans.push_back({i, j - 1});
        i = j;
    }
    int siz = ans.size();
    vector<int> tmp = ans.back();
    set<int> SS;
    for (int k = tmp[0]; k <= tmp[1]; ++k) SS.insert(a[k]);
    if (SS.size() == tmp[1] - tmp[0] + 1) {
        ans[siz - 2][1] = tmp[1];
        ans.pop_back();
        siz -= 1;
    }
    cout << siz << endl;
    for (int i = 0; i < siz; ++i) {
        cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << endl;
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
