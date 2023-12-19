// https://www.luogu.com.cn/problem/SP2371
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
        for (; x <= n; x += x & -x) t[x] = max(t[x], v);
    }

    int ask(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res = max(res, t[x]);
        return res;
    }

    int ask_range(int l, int r) {return ask(r) - ask(l - 1);}

    
    void clear(int x) {
        for (; x <= n; x += x & -x) t[x] = 0;
    }
};


struct Q {
    int a, b, c;    // a表示第一维元素, b表示第二维元素, c表示第三维元素
    int res;        // res表示当前节点的答案
    bool operator < (const Q& x) const {
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
        return c < x.c;
    };
};

vector<Q> d;
BIT B(100005);

void cdq(int l, int r) {
    // 在计算[m + 1, r]前, 应将[l, m]的贡献计算到[m + 1, r]中, 所以要先左边, 再合并, 最后算右边
    if (l == r) return;
    int m = l + r >> 1;
    cdq(l, m);
    sort(d.begin() + l, d.begin() + m + 1, [](Q& x, Q& y) { return x.b != y.b ? x.b < y.b : x.c < y.c; });
    sort(d.begin() + m + 1, d.begin() + r + 1, [](Q& x, Q& y) { return x.b != y.b ? x.b < y.b : x.c < y.c; });
    int i, j = l;
    for (i = m + 1; i <= r; i++) {
        while (d[i].b > d[j].b && j <= m) {
            B.add(d[j].c, d[j].res);
            j++;
        }
        d[i].res = max(d[i].res, B.ask(d[i].c - 1) + 1);
    }
    for (i = l; i < j; i++) {   // 清空左半边的影响, 再计算右半边, 避免重复计算
        B.clear(d[i].c);
    }
    sort(d.begin() + m + 1, d.begin() + r + 1);   // 恢复有序
    cdq(m + 1, r);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    vector<int> idx;
    for (int i = 0; i < n; i++) {
        int a = i, b, c;
        cin >> b >> c;
        d.push_back({a, b, c, 1});
        idx.push_back(c);
    }
    // 离散化
    sort(idx.begin(), idx.end());
    idx.erase(unique(idx.begin(), idx.end()), idx.end());
    for (int i = 0; i < n; i++) {
        d[i].c = lower_bound(idx.begin(), idx.end(), d[i].c) - idx.begin() + 1;
    }
    sort(d.begin(), d.end());
    cdq(0, n - 1);
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, d[i].res);
    }
    cout << res << endl;
    return 0;
}
