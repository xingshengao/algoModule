#include <bits/stdc++.h>
using namespace std;
using LL = long long;

template <class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};
struct Info {
    LL x;
    Info() { x = 0; }
    Info(LL x) { this->x = x; }
};

Info operator+(Info a, Info b) {
    Info ans;
    ans.x = a.x + b.x;
    return ans;
}

// 区间和线段树, SegmentTree<LL> seg(n + 1)即可, 不需要Info

// 493. 翻转对
// 给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
// 你需要返回给定数组中的重要翻转对的数量

// 线段树的modify(x, v)是将x的值 修改为v
// 树状数组的add(x, v)是将x的值添加v
class Solution1 {
   public:
    int reversePairs(vector<int>& nums) {
        LL n = nums.size();
        vector<LL> arr;
        for (LL i = 0; i < n; ++i) {
            arr.push_back(1LL * nums[i]);
            arr.push_back(2LL * nums[i]);
        }

        // 离散化
        auto Uni = [](vector<LL>& A) -> vector<LL> {
            vector<LL> ans(A);
            sort(ans.begin(), ans.end());
            ans.erase(unique(ans.begin(), ans.end()), ans.end());
            return ans;
        };
        vector<LL> A = Uni(arr);
        map<LL, LL> mp;
        for (int i = 0; i < A.size(); ++i) {
            mp[A[i]] = i + 1;
        }

        SegmentTree<LL> seg(A.size() + 1);
        LL ans = 0;
        for (LL i = 0; i < n; ++i) {
            ans += seg.rangeQuery(mp[2LL * nums[i]] + 1, A.size() + 1);  // 线段树查询左闭右开
            // 之前的值
            LL pre = seg.rangeQuery(mp[1LL * nums[i]], mp[1LL * nums[i]] + 1);

            // modify是单点更新, 注意是更新为某个值, 所以, 进行加操作时, 需要 modify 成pre + delta
            seg.modify(mp[1LL * nums[i]], pre + 1LL);
        }
        return ans;
    }
};