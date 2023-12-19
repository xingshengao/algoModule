// https://www.luogu.com.cn/problem/P1429
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define lc t[p].l
#define rc t[p].r

using namespace std;

double res = 2e18;
int n, root, cur;   // root根, cur当前节点

struct KD {     // KD树节点信息
    int l, r;   // 左右孩子
    double V[2];    // 点的坐标值
    double L[2], U[2];  // 子树区域的坐标范围
};
vector<KD> t;

void pushup(int p) {    // 更新p子树区域的坐标范围
    for (int i = 0; i < 2; i++) {
        t[p].L[i] = t[p].U[i] = t[p].V[i];
        if (lc) {
            t[p].L[i] = min(t[p].L[i], t[lc].L[i]);
            t[p].U[i] = max(t[p].U[i], t[lc].U[i]);
        }
        if (rc) {
            t[p].L[i] = min(t[p].L[i], t[rc].L[i]);
            t[p].U[i] = max(t[p].U[i], t[rc].U[i]);
        }
    }
}

int build(int l, int r, int k) {
    if (l > r) return 0;
    int m = l + r >> 1;
    nth_element(t.begin() + l, t.begin() + m, t.begin() + r + 1, [&](KD& a, KD& b) {
        return a.V[k] < b.V[k];
    });
    t[m].l = build(l, m - 1, k ^ 1);
    t[m].r = build(m + 1, r, k ^ 1);
    pushup(m);
    return m;
}

double sq(double x) {
    return x * x;
}

double dis(int p) { // 当前点到p点的距离
    double s = 0;
    for (int i = 0; i < 2; i++) {
        s += sq(t[cur].V[i] - t[p].V[i]);
    }
    return s;
}

double dis2(int p) {    // 查询点到p子树区域的最小距离
    if (!p) return 2e18;
    double s = 0;
    for (int i = 0; i < 2; i++) {
        s += sq(max(t[cur].V[i] - t[p].U[i], 0.0)) + sq(max(t[p].L[i] - t[cur].V[i], 0.0));
    }
    return s;
}

void query(int p) { // 查询当前点的最小距离
    if (!p) return;
    if (p != cur) res = min(res, dis(p));
    double dl = dis2(lc), dr = dis2(rc);
    if (dl < dr) {
        if (dl < res) query(lc);
        if (dr < res) query(rc);
    } else {
        if (dr < res) query(rc);
        if (dl < res) query(lc);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(4);
    cin >> n;
    t = vector<KD> (n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i].V[0] >> t[i].V[1];
    }
    root = build(1, n, 0);
    for (cur = 1; cur <= n; cur++) {
        query(root);
    }
    cout << sqrt(res) << endl;
    return 0;
}
