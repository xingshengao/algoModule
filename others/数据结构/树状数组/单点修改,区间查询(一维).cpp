// 例题:https://loj.ac/p/130
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct BIT {    // 下标从1开始

    int n;
    vector<int> t;

    BIT(int _n) {
        n = _n + 4;
        t.resize(_n + 5);
    }

    void add(int x, int v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }

    int ask(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += t[x];
        return res;
    }

    int ask_range(int l, int r) {return ask(r) - ask(l - 1);}
};

signed main() {
    int n, m;
    cin >> n >> m;
    BIT B(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        B.add(i, a);
    }
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            B.add(l, r);
        } else {
            cout << B.ask_range(l, r) << endl;
        }
    }
    return 0;
}

