// https://www.luogu.com.cn/problem/P1903
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int n, m;

struct query {
    int l, r, id;
    int pre;   // 上一次修改操作的时间

    bool operator < (const query& x) const {
        int m = pow(n, 0.666);  // 注意块的大小必须是n^(2/3)
        if (l / m != x.l / m) return l < x.l;
        if (r / m != x.r / m) return r < x.r;
        return pre < x.pre;
    }
};

struct Change {
    int pos, val;   // 修改操作的位置和值
};

int nowRes = 0;
vector<int> v, cnt, res;
vector<query> querys;
vector<Change> changes;

void add(int pos) {
    if (cnt[v[pos]] == 0) nowRes++;
    cnt[v[pos]]++;
}

void del(int pos) {
    cnt[v[pos]]--;
    if (cnt[v[pos]] == 0) nowRes--;
}

void upd(int updTime, int i) {
    if (querys[i].l <= changes[updTime].pos && changes[updTime].pos <= querys[i].r) {
        int oldValue = v[changes[updTime].pos];
        cnt[oldValue]--;
        if (cnt[oldValue] == 0) nowRes--;
        int newValue = changes[updTime].val;
        cnt[newValue]++;
        if (cnt[newValue] == 1) nowRes++;
    }
    swap(changes[updTime].val, v[changes[updTime].pos]);
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    v.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    res.resize(m + 1);
    querys.resize(m + 1);
    changes.resize(m + 1);
    cnt.resize(1000000);
    int Qcnt = 0, Ccnt = 0;
    for (int i = 1; i <= m; i++) {
        string op;
        cin >> op;
        if (op == "Q") {
            Qcnt++;
            int l, r;
            cin >> l >> r;
            querys[Qcnt].l = l;
            querys[Qcnt].r = r;
            querys[Qcnt].pre = Ccnt;
            querys[Qcnt].id = Qcnt;
        } else {
            Ccnt++;
            int pos, v;
            cin >> pos >> v;
            changes[Ccnt].pos = pos;
            changes[Ccnt].val = v;
        }
    }
    sort(querys.begin() + 1, querys.begin() + Qcnt + 1);
    int l = 1, r = 0, updTime = 0;
    for (int i = 1; i <= Qcnt; i++) {
        int ql = querys[i].l, qr = querys[i].r, id = querys[i].id;
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) del(l++);
        while (r > qr) del(r--);
        while (updTime < querys[i].pre) upd(++updTime, i);
        while (updTime > querys[i].pre) upd(updTime--, i);
        res[id] = nowRes;
    }
    for (int i = 1; i <= Qcnt; i++) {
        cout << res[i] << endl;
    }
}