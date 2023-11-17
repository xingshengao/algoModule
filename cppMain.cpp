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
bool check(string& a, string& b) {
    int cnt = 0;
    for (int i = 0; i < a.size(); ++i) {
        cnt += a[i] != b[i];
        if (cnt > 1) return false;
    }
    return cnt == 1;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> vec(n);
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; ++i) cin >> vec[i];
    do {
        bool flag = true;
        for (int i = 0; i + 1 < n; ++i) {
            if (not check(vec[i], vec[i + 1])) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "Yes" << endl;
            return;
        }
    } while (next_permutation(vec.begin(), vec.end()));
    cout << "No" << endl;
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