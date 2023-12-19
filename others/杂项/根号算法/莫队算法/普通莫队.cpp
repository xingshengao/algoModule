// https://loj.ac/p/3751
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int n, m;

struct query {
    int l, r, id;

    bool operator < (const query& x) const {
        int m = sqrt(n);
        if (l / m != x.l / m) return l < x.l;
        return (l / m) & 1 ? (r < x.r) : (r > x.r);
    }
};

int nowRes = 0;
vector<int> v, cnt, res;
vector<query> querys;

void add(int pos) {
    if (cnt[v[pos]] == 0) nowRes++;
    cnt[v[pos]]++;
}

void del(int pos) {
    cnt[v[pos]]--;
    if (cnt[v[pos]] == 0) nowRes--;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    v.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    cin >> m;
    res.resize(m + 1);
    querys.resize(m + 1);
    cnt.resize(1000000);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        querys[i] = {l, r, i};
    }
    sort(querys.begin() + 1, querys.begin() + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        int ql = querys[i].l, qr = querys[i].r, id = querys[i].id;
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) del(l++);
        while (r > qr) del(r--);
        res[id] = nowRes;
    }
    for (int i = 1; i <= m; i++) {
        cout << res[i] << endl;
    }
}