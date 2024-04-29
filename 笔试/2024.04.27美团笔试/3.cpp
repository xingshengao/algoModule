#include <bits/stdc++.h>
#define int long long
using namespace std;
// static constexpr long long mod = 1000000007;
// 数组合并，给定一个分割数组最小值，求有多少种分割的方法
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    // dfs(i, j)代表考虑从i往后的数字，当前和为j，组成的满足的方案数量是多少
    int sum = accumulate(a.begin(), a.end(), 0LL);
    vector memo(n + 10, vector<int>(sum + 1, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int {
        if (i == n) {
            if (j >= k)
                return 1;
            else
                return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int res = 0;
        if (j >= k)
            res += dfs(i + 1, a[i]) + dfs(i + 1, j + a[i]);  // 新开一个分组或者继续这个分组

        else
            res += dfs(i + 1, j + a[i]);  // 和不够k只能继续这个分组
        res = (res % mod + mod) % mod;
        return memo[i][j] = res;
    };
    cout << dfs(0, 0) << endl;
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