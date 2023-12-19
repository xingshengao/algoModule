// https://www.luogu.com.cn/problem/P2048
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct SegTree {
    
    int n, inf = 2e9;
    vector<int> v, v_pos;
    
    SegTree() {}
    SegTree(int n) {
        this->n = n;
        v = vector<int> (n * 4 + 5);
        v_pos = vector<int> (n * 4 + 5);
    }

    void change(int p, int l, int r, int pos, int val) {    // 单点修改
        if (l == r && l == pos) {
            v[p] = val;
            v_pos[p] = pos;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m) {
            change(p * 2, l, m, pos, val);
        }
        if (m < pos) {
            change(p * 2 + 1, m + 1, r, pos, val);
        }
        if (v[p * 2] >= v[p * 2 + 1]) {
            v[p] = v[p * 2];
            v_pos[p] = v_pos[p * 2];
        } else {
            v[p] = v[p * 2 + 1];
            v_pos[p] = v_pos[p * 2 + 1];
        }
    }

    pair<int, int> query(int p, int l, int r, int ql, int qr) {    // 查询区间最大值和最大值下标
        if (ql <= l && r <= qr) {
            return {v[p], v_pos[p]};
        }
        int m = l + r >> 1;
        pair<int, int> res = {-1e9, -1e9};
        pair<int, int> res_l = {-1e9, -1e9};
        pair<int, int> res_r = {-1e9, -1e9};
        if (ql <= m) {
            res_l = query(p * 2, l, m, ql, qr);
        }
        if (qr > m) {
            res_r = query(p * 2 + 1, m + 1, r, ql, qr);
        }
        if (res_l.first >= res_r.first) {
            res = res_l;
        } else {
            res = res_r;
        }
        return res;
    }

    void change(int pos, int val) {
        change(1, 0, n, pos, val);
    }

    pair<int, int> query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }

};


struct Q {
    int id, l, r, pos, val;
    bool operator < (const Q& x) const {
        return val > x.val;
    };
};

int get(int l, int r, vector<int>& pre) {
    return pre[r] - pre[l - 1];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> v(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pre[i] = pre[i - 1] + v[i];
    }
    SegTree S(n);
    for (int i = 1; i <= n; i++) {
        S.change(i, pre[i]);
    }
    multiset<Q> s;
    for (int i = 1; i <= n; i++) {
        int ll = i + l - 1, rr = min(n, i + r - 1);
        if (ll > n) break;
        int pos = S.query(ll, rr).second;
        s.insert({i, ll, rr, pos, get(i, pos, pre)});
    }
    int res = 0;
    while (k--) {
        Q now = *s.begin();
        s.erase(s.begin());
        res += now.val;
        int ll = now.l, rr = now.pos - 1;
        if (ll <= rr) {
            int pos = S.query(ll, rr).second;
            s.insert({now.id, ll, rr, pos, get(now.id, pos, pre)});
        }
        ll = now.pos + 1, rr = now.r;
        if (ll <= rr) {
            int pos = S.query(ll, rr).second;
            s.insert({now.id, ll, rr, pos, get(now.id, pos, pre)});
        }
    }
    cout << res << endl;
    return 0;
}