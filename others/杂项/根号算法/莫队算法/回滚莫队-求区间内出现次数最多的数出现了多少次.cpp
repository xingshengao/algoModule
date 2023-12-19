// https://www.luogu.com.cn/problem/P3709
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int n, m, siz, tot;
int nowRes = 0;
vector<int> v, tv, cnt, tmpcnt, res;
vector<int> L, R, pos;

struct query {
    int l, r, id;

    bool operator < (const query& x) const {
        if (pos[l] != pos[x.l]) return pos[l] < pos[x.l];
        return r < x.r;
    }
};
vector<query> querys;

void add(int pos, int& res) {
    cnt[tv[pos]]++;
    res = max(res, cnt[tv[pos]]);
}

void del(int pos) {
    cnt[tv[pos]]--;
}

void init() {
    siz = sqrt(n);
    tot = n / siz;
    L = vector<int> (tot + 5);
    R = vector<int> (tot + 5);
    pos = vector<int> (n + 1);
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * siz + 1;
        R[i] = i * siz;
    }
    if (R[tot] < n) {
        tot++;
        L[tot] = R[tot - 1] + 1;
        R[tot] = n;
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    v.resize(n + 1);
    tv.resize(n + 1);
    res.resize(m + 1);
    querys.resize(m + 1);
    cnt.resize(1000000);
    tmpcnt.resize(1000000);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        tv[i] = v[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> querys[i].l >> querys[i].r;
        querys[i].id = i;
    }
    init();
    // 排序询问
    for (int i = 1; i <= tot; i++) {
        for (int j = L[i]; j <= R[i]; j++) {
            pos[j] = i;
        }
    }
    sort(querys.begin() + 1, querys.begin() + m + 1);
    // 离散化
    vector<int> t = v;
    sort(t.begin() + 1, t.begin() + n + 1);
    for (int i = 1; i <= n; i++) {
        tv[i] = lower_bound(t.begin() + 1, t.begin() + n + 1, tv[i]) - t.begin();
    }

    int l = 1, r = 0, last_block = 0;
    for (int i = 1; i <= m; i++) {
        int ql = querys[i].l, qr = querys[i].r, id = querys[i].id;
        // 询问的左右端点同属于一个块则暴力扫描回答
        if (pos[ql] == pos[qr]) {
            for (int j = ql; j <= qr; j++) {
                tmpcnt[tv[j]]++;
            }
            for (int j = ql; j <= qr; j++) {
                res[id] = max(res[id], tmpcnt[tv[j]]);
            }
            for (int j = ql; j <= qr; j++) {
                tmpcnt[tv[j]]--;
            }
            continue;
        }
        // 访问到了新的块则重新初始化莫队区间
        if (pos[ql] != last_block) {
            while (r > R[pos[ql]]) del(r--);
            while (l < R[pos[ql]] + 1) del(l++);
            nowRes = 0;
            last_block = pos[ql];
        }
        // 扩展右端点
        while (r < qr) add(++r, nowRes);
        // 扩展左端点
        int tmpRes = nowRes;
        int tl = l;
        while (tl > ql) add(--tl, tmpRes);
        res[id] = tmpRes;
        //回滚
        while (tl < l) del(tl++);

    }
    for (int i = 1; i <= m; i++) {
        cout << -res[i] << endl;
    }
}