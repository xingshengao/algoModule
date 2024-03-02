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


static constexpr long long mod = 998244353;
// static constexpr long long mod = 1000000007;
unordered_set<int> A;  // 预处理1-2e9的所有平方数字

int init = []() {
    for (int x = 1; x * x <= 2e9; ++x) {
        A.insert(x * x);
    }
    return 0;
}();
void solve() {
    int N;
    cin >> N;
    string s = to_string(N);
    // 二进制枚举选哪些数字
    int m = s.size();  // 数字的位数
    int ans = 1e9;
    // cout << m << endl;
    for (int mask = 0; mask < (1 << m); ++mask) {
        // 注意最高位不能是0
        int first = -1;  // 最高位是什么数字
        int tot = 0;     // 当前数字
        int cnt = 0;
        for (int j = m - 1; j >= 0; --j) {
            if (mask >> j & 1) {
                first = s[m - 1 - j] - '0';
                break;
            }
        }
        if (first == 0) continue;
        for (int j = m - 1; j >= 0; --j) {
            if (mask >> j & 1) {
                tot = tot * 10 + (s[m - 1 - j] - '0');
                cnt++;
            }
        }
        if (A.count(tot)) {
            chmin(ans, m - cnt);
        }
    }
    cout << (ans == 1e9 ? -1 : ans) << endl;
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