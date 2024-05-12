#include <bits/stdc++.h>
#define int long long
using namespace std;

using PDD = pair<double, double>;

// 复数乘法
PDD mul(PDD& a, PDD& b) { 
    return PDD(a.first * b.first - a.second * b.second, a.first * b.second + a.second * b.first); 
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    // 用户U
    vector<pair<double, double>> U(n);
    // m个用户V
    vector V(m, vector<PDD>(n));
    for (int i = 0; i < n; ++i) {
        cin >> U[i].first >> U[i].second;
    }
    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < n; ++i) {
            cin >> V[k][i].first >> V[k][i].second;
        }
    }
    // 共轭转置， 先转置再取共轭
    // 只有一列，转置就是一列变为一行，直接取共轭
    for (int i = 0; i < n; ++i) {
        U[i].second = -U[i].second;
    }
    vector<double> ans(m);
    for (int k = 0; k < m; ++k) {
        // 第k个用户
        double a = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            PDD res = mul(U[i], V[k][i]);
            a += res.first;
            b += res.second;
        }
        ans[k] = a * a + b * b;
    }
    double mn = 1e9;
    int mn_id = 0;
    for (int i = 0; i < m; ++i) {
        if (ans[i] < mn) {
            mn = ans[i];
            mn_id = i;
        }
    }
    cout << mn_id << endl;
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