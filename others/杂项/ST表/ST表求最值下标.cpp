// https://www.luogu.com.cn/problem/P2048
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct ST {

    vector<vector<int>> st;     // 存最大值
    vector<vector<int>> pos;    // 存最大值下标

    ST() {}
    ST(vector<int> &a) {    // 构造函数
        int n = a.size();
        int k = __lg(n);
        st = vector<vector<int>> (n, vector<int> (k + 1));
        pos = vector<vector<int>> (n, vector<int> (k + 1));
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i];
            pos[i][0] = i;
        }
        for(int i = 1; i <= k; i++) {
            for(int l = 0, r = l + (1 << i) - 1; r < n; l++, r++) {
                int m = l + (1 << (i - 1));
                if (st[l][i - 1] >= st[m][i - 1]) { // 相等时返回左边下标用 >=, 相等时返回右边下标用 >
                    st[l][i] = st[l][i - 1];
                    pos[l][i] = pos[l][i - 1];
                } else {
                    st[l][i] = st[m][i - 1];
                    pos[l][i] = pos[m][i - 1];
                }
            }
        }
    }
    
    int query_pos(int l, int r) {   // 查询最大值下标
        int k = __lg(r - l + 1);
        int pos1 = pos[l][k], pos2 = pos[r - (1 << k) + 1][k];
        return st[pos1][0] >= st[pos2][0] ? pos1 : pos2; // 相等时返回左边下标用 >=, 相等时返回右边下标用 >
    }

    int query(int l, int r) {   // 查询最大值
        return st[query_pos(l, r)][0];
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
    ST S(pre);
    multiset<Q> s;
    for (int i = 1; i <= n; i++) {
        int ll = i + l - 1, rr = min(n, i + r - 1);
        if (ll > n) break;
        int pos = S.query_pos(ll, rr);
        s.insert({i, ll, rr, pos, get(i, pos, pre)});
    }
    int res = 0;
    while (k--) {
        Q now = *s.begin();
        s.erase(s.begin());
        res += now.val;
        int ll = now.l, rr = now.pos - 1;
        if (ll <= rr) {
            int pos = S.query_pos(ll, rr);
            s.insert({now.id, ll, rr, pos, get(now.id, pos, pre)});
        }
        ll = now.pos + 1, rr = now.r;
        if (ll <= rr) {
            int pos = S.query_pos(ll, rr);
            s.insert({now.id, ll, rr, pos, get(now.id, pos, pre)});
        }
    }
    cout << res << endl;
    return 0;
}