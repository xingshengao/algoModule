// 例题:https://loj.ac/p/133
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct BIT {

    int n, m;
    vector<vector<int>> t;

    BIT(int _n, int _m) {
        n = _n;
        m = _m;
        t.resize(n + 1, vector<int> (m + 1));
    }

    void add(int x, int y, int v) {
        for (; x <= n; x += x & -x) {
            for (int j = y; j <= m; j += j & -j) {
                t[x][j] += v;
            }
        }
    }

    int ask(int x, int y) {
        int sum = 0;
        for (; x; x -= x & -x) {
            for (int j = y; j; j -= j & -j) {
                sum += t[x][j];
            }
        }
        return sum;
    }

    int get_range(int x1, int y1, int x2, int y2) {
        return ask(x2, y2) + ask(x1 - 1, y1 - 1) - ask(x1 - 1, y2) - ask(x2, y1 - 1);
    }

};

signed main() {
    int n, m, op;
    cin >> n >> m;
    BIT B(n, m);
    while (cin >> op) {
        if (op == 1) {
            int x, y, v;
            cin >> x >> y >> v;
            B.add(x, y, v);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << B.get_range(x1, y1, x2, y2) << endl;
        }
    }
    return 0;
}
