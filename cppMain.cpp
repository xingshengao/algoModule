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
    std::string s;
    cin >> s;
    int n = s.size();
    int cnt1 = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') cnt1 += 1;
    }
    if (cnt1 == 0) {
        cout << s << endl;
        return;
    }
    string t;
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] != '1') t += s[i];
    }
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == '2') {
            idx = i;
            break;
        }
    }
    if (idx == -1) {  // 说明没有2
        cout << t + string(cnt1, '1') << endl;
        return;
    } else if (idx == 0) {  // 说明第一个是2
        cout << string(cnt1, '1') + t << endl;
        return;
    }
    cout << t.substr(0, idx) + string(cnt1, '1') + t.substr(idx);
}
signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 2;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
