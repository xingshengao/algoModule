// https://www.luogu.com.cn/problem/P3810
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

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


struct Q {
    int a, b, c;    // a表示第一维元素, b表示第二维元素, c表示第三维元素
    int cnt, res;   // cnt表示(a, b, c)这个三元组出现的次数, res表示当前节点的答案
    bool operator < (const Q& x) const {
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
        return c < x.c;
    };
};

vector<Q> d;
BIT B(200001);

void cdq(int l, int r) {
    if (l == r) return;
    int m = l + r >> 1;
    cdq(l, m);
    cdq(m + 1, r);
    sort(d.begin() + l, d.begin() + m + 1, [](Q& x, Q& y) { return x.b != y.b ? x.b < y.b : x.c < y.c; });
    sort(d.begin() + m + 1, d.begin() + r + 1, [](Q& x, Q& y) { return x.b != y.b ? x.b < y.b : x.c < y.c; });
    int i, j = l;
    for (i = m + 1; i <= r; i++) {
        while (d[i].b >= d[j].b && j <= m) {
            B.add(d[j].c, d[j].cnt);
            j++;
        }
        d[i].res += B.ask(d[i].c);
    }
    for (i = l; i < j; i++) {
        B.add(d[i].c, -d[i].cnt);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> v(n, vector<int> (3));
    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }
    // cdq的过程中只有左边的能贡献右边
    // 为防止右边和左边有相同元素, 导致右边能贡献左边, 需要进行去重操作
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        if (d.size() && v[i][0] == d.back().a && v[i][1] == d.back().b && v[i][2] == d.back().c) {
            d.back().cnt++;
        } else {
            d.push_back({v[i][0], v[i][1], v[i][2], 1, 0});
        }
    }
    int m = d.size();
    cdq(0, m - 1);
    vector<int> res(n);
    // 算答案时, 记得计算相同元素产生的贡献
    for (int i = 0; i < m; i++) {
        res[d[i].res + d[i].cnt - 1] += d[i].cnt;
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << endl;
    }
    return 0;
}
