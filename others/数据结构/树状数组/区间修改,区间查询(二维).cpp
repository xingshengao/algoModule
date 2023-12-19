// 例题:https://loj.ac/p/135
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct BIT {

    int n, m;
    vector<vector<int>> t1, t2, t3, t4;

    BIT(int _n, int _m) {
        n = _n;
        m = _m;
        t1.resize(n + 1, vector<int> (m + 1));
        t2.resize(n + 1, vector<int> (m + 1));
        t3.resize(n + 1, vector<int> (m + 1));
        t4.resize(n + 1, vector<int> (m + 1));
    }

    void add(int a, int b, int k) {
        for (int i = a; i <= n; i += i & -i) {
            for (int j = b; j <= m; j += j & -j) {
                t1[i][j] += k;
                t2[i][j] += k * a;
                t3[i][j] += k * b;
                t4[i][j] += k * a * b;
            }
        }
    }

    int sum(int a, int b) {
        int ans = 0;
        for (int i = a; i > 0; i -= i & -i) {
            for (int j = b; j > 0; j -= j & -j) {
                ans += t1[i][j] * ((a + 1) * (b + 1)) - t2[i][j] * (b + 1) - t3[i][j] * (a + 1) + t4[i][j];
            }
        }
        return ans;
    }

    void range_add(int a, int b, int c, int d, int k) {
        add(a, b, k);
        add(c + 1, d + 1, k);
        add(a, d + 1, -k);
        add(c + 1, b, -k);
    }

    int range_sum(int a, int b, int c, int d) {
        return sum(a - 1, b - 1) + sum(c, d) - sum(a - 1, d) - sum(c, b - 1);
    }
};

signed main() {
    int n, m, op, a, b, c, d, k;
    cin >> n >> m;
    BIT B(n, m);
    while (cin >> op) {
        if (op == 1) {
            cin >> a >> b >> c >> d >> k;
            B.range_add(a, b, c, d, k);
        } else {
            cin >> a >> b >> c >> d;
            cout << B.range_sum(a, b, c, d) << endl;
        }
    }
    return 0;
}
