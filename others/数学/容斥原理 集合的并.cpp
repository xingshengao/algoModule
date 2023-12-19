// https://www.luogu.com.cn/problem/SP6285
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 容斥原理: 集合的并等于集合的交的交错和(奇正偶负)
// 注: 可以画韦恩图来理解

int lcm(int a, int b) {
    return a * b / __gcd(a, b);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, k;
    cin >> n >> k;
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
    }
    int res = 0;
    for (int i = 1; i < (1 << k); i++) {
        int t = 1, cnt = 0;
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) {
                t = lcm(t, v[j]);
                cnt++;
            }
        }
        if (cnt % 2 == 1) { // 奇正
            res += n / t;
        } else {            // 偶负
            res -= n / t;
        }
    }
    cout << n - res << endl;
    return 0;
}
