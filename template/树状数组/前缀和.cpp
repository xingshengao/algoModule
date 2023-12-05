#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
public:
    LL tr[100010]{0}; // 维护前缀和.
    LL lowbit(LL x) {return x & (-x);}
    void add(LL x, LL v) {
        for (; x < 100010; x += lowbit(x)) tr[x] += v;
    }
    LL query(LL x) {
        LL res = 0;
        for (; x; x -= lowbit(x)) res += tr[x];
        return res;
    }
    LL sumRange(LL l, LL r) { // [L, R]的和, 下标都从1开始
        return query(r) - query(l - 1);
    }

};