#include <bits/stdc++.h>
using namespace std;
// 维护区间最大值的树状数组
struct BIT {
   public:
    vector<int> tr;
    int n;
    const int INF = 1e9;
    BIT(int n) {
        this->n = n;
        this->tr.resize(n + 1, -INF);
    }
    int lowbit(int x) { return x & (-x); }
    void modify(int x, int v) {
        for (; x <= n; x += lowbit(x)) tr[x] = max(tr[x], v);
    }
    int query(int x) {
        int res = -INF;
        for (; x; x -= lowbit(x)) res = max(res, tr[x]);
        return res;
    }
};