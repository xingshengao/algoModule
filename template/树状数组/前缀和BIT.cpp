#include <bits/stdc++.h>
using namespace std;
struct Fenwick {
    vector<int> nums;
    vector<int> tr;  // 书关键区间元素和, 下标从1开始
    int n;
    Fenwick() {}
    Fenwick(vector<int>& nums) {
        this->nums = nums;
        this->n = nums.size();
        this->tr.resize(n + 1);
        for (int i = 1; i <= n + 1; ++i) {
            tr[i] += nums[i - 1];     // 树状数组右端点为i
            int nxt = i + lowbit(i);  // 下一个关键区间的右端点
            if (nxt <= n) tr[nxt] += tr[i];
        }
    }
    int lowbit(int x) { return x & (-x); }
    int query(int i) {  // 树状数组前缀和
        int s = 0;
        for (; i > 0; i -= lowbit(i)) {
            s += tr[i];
        }
        return s;
    }
    void modify(int index, int v) {
        int delta = v - nums[index];
        nums[index] = v;
        for (int i = index + 1; i <= tr.size(); i += lowbit(i)) {
            tr[i] += delta;
        }
    }
    int rangeSum(int l, int r) { return query(r + 1) - query(l); }
};