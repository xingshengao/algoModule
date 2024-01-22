#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// 两个 multiset 维护滑动窗口中的前 K 小值
struct Magic {
    int K;
    // st1 保存前 K 小值，st2 保存其它值
    multiset<LL> st1, st2;
    // sm 表示 st1 中所有数的和
    LL sm;

    Magic(int K) : K(K), sm(0) {}

    // 调整 st1 和 st2 的大小，保证调整后 st1 保存前 K 小值
    void adjust() {
        while (st1.size() < K and st2.size() > 0) {
            LL t = *(st2.begin());
            st1.insert(t);
            sm += t;
            st2.erase(st2.begin());
        }
        while (st1.size() > K) {
            LL t = *prev(st1.end());
            st2.insert(t);
            st1.erase(prev(st1.end()));
            sm -= t;
        }
    }

    // 插入元素 x
    void add(LL x) {
        if (!st2.empty() and x >= *(st2.begin()))
            st2.insert(x);
        else
            st1.insert(x), sm += x;
        adjust();
    }

    // 删除元素 x
    void del(LL x) {
        auto it = st1.find(x);
        if (it != st1.end())
            st1.erase(it), sm -= x;
        else
            st2.erase(st2.find(x));
        adjust();
    }
};

// 使用举例
// 3013. 将数组分成最小总代价的子数组 II

// 给你一个下标从 0 开始长度为 n 的整数数组 nums 和两个 正 整数 k 和 dist 。

// 一个数组的 代价 是数组中的 第一个 元素。比方说，[1,2,3] 的代价为 1 ，[3,4,1] 的代价为 3 。

// 你需要将 nums 分割成 k 个 连续且互不相交 的子数组，满足 第二 个子数组与第 k 个子数组中第一个元素的下标距离 不超过 dist 。换句话说，如果你将 nums
// 分割成子数组 nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)] ，那么它需要满足 ik-1 - i1 <= dist 。

// 请你返回这些子数组的 最小 总代价

class Solution {
   public:
    long long minimumCost(vector<int>& nums, int K, int dist) {
        // 本题等价于在nums[1]~nums[n - 1]之间,长度为dist+1的滑动窗口, 选出最小的k-1个数字,
        int n = nums.size();
        Magic magic(K - 1);
        LL ans = 1e18;

        // 滑窗容量扩展到dist+1, [1: dist+1]
        for (int i = 1; i <= dist + 1 and i < n; ++i) {
            magic.add(nums[i]);
        }
        ans = min(ans, nums[0] + magic.sm);
        // 维护定长滑动窗口,
        for (int r = dist + 2; r < n; ++r) {
            magic.add(nums[r]);
            magic.del(nums[r - (dist + 1)]);
            ans = min(ans, nums[0] + magic.sm);
        }
        return ans;
    }
};