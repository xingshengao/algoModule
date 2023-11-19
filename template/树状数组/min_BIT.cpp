#include <bits/stdc++.h>
using namespace std;
// 维护区间最小值的树状数组
struct BIT {
   public:
    vector<int> tr;
    int n;
    const int INF = 1e9;
    BIT(int n) {
        this->n = n;
        this->tr.resize(n + 1, INF);
    }
    int lowbit(int x) { return x & (-x); }
    void modify(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tr[i] = min(tr[i], val);
        }
    }
    int query(int pos) {
        int res = INF;
        for (int i = pos; i; i -= lowbit(i)) {
            res = min(res, tr[i]);
        }
        return res;
    }
};