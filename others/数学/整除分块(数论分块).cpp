// https://www.luogu.com.cn/problem/AT_abc230_e
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 性质1: 分块的块数 <= 2*根号n
// 性质2: i所在的块的右端点为 n / (n / i)

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    int res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        int k = n / l;
        r = n / k;
        res += k * (r - l + 1);
    }
    cout << res << endl;
    return 0;
}
