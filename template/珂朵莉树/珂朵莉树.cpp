#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// 珂朵莉树
// 应用: 有区间赋值操作且数据随机的题目
// 珂朵莉树的思想在于随机数据下的区间赋值操作很可能让大量元素变为同一个数。所以我们以三元组<l,r,v>的形式保存数据
// [l, r]中的元素的值都是v

struct node {
    int l, r;
    mutable int v;  // mutable使得当整个结构体为const时，标为mutable的成员仍可变
    node() {}
    node(int _l, int _r, int _v) { l = _l, r = _r, v = _v; }
    bool operator<(const node& a) const { return l < a.l; }  // 使用set存储node需要重载小于运算符号
};

struct ODT {
    int n;
    set<node> odt;
    ODT() {}
    ODT(int n) {  // 构造函数
        this->n = n;
    }
    void init(int n) { this->n = n; }
    // 分裂区间, 将[l, r, v] 分裂成[l, x - 1, v] 和 [x, r, v]
    auto split(int x) {
        if (x > n) return odt.end();
        auto it = --odt.upper_bound({x, 0, 0});  // 寻找左端点大于pos的第一个节点 的上一个节点/*  */
        if (it->l == x) return it;               // 如果已经存在以pos为左端点的节点，直接返回
        int l = it->l, r = it->r, v = it->v;
        odt.erase(it);
        odt.insert({l, x - 1, v});
        return odt.insert({x, r, v}).first;  // 返回以x开头那个节点的迭代器
    }

    // 区间赋值
    void assign(int l, int r, int v) {
        auto itr = split(r + 1), itl = split(l);  // 将[l, r]区间断开, itr指r+1开始的区间, itl指向l开始的区间
        odt.erase(itl, itr);                      // 删除[itl, itr)之间的区间数据
        odt.insert({l, r, v});                    // 插入新区间数据
    }

    // 区间加法
    void add(int l, int r, int v) {
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl) {
            itl->v += v;
        }
    }

    // 区间求和
    int query_sum(int l, int r) {
        int res = 0;
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl) {
            res += (itl->r - itl->l + 1) * itl->v;
        }
        return res;
    }

    // 判断区间[l, r]中间是否全都不是为0的数字
    bool check(int l, int r) {
        auto itr = split(r + 1);
        auto itl = split(l);
        auto it = itl;
        for (; it != itr; it++) {
            if (it->v == 0) return false;
        }
        return true;
    }

    // 区间求第k小
    int kth(int l, int r, int k) {
        auto end = split(r + 1);
        vector<tuple<int, int>> v;  // 存节点的值和区间长度
        for (auto it = split(l); it != end; it++) {
            v.push_back({it->v, it->r - it->l + 1});
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++) {
            k -= get<1>(v[i]);
            if (k <= 0) {
                return get<0>(v[i]);
            }
        }
        return -1;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    ODT O(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        O.odt.insert({i, i, a});
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << O.kth(l, r, k) << endl;
    }
    return 0;
}

// 使用举例
// 2276: 给你区间的 空 集，请你设计并实现满足要求的数据结构：

// 新增：添加一个区间到这个区间集合中。
// 统计：计算出现在 至少一个 区间中的整数个数。
// 实现 CountIntervals 类：

// CountIntervals() 使用区间的空集初始化对象
// void add(int left, int right) 添加区间 [left, right] 到区间集合之中。
// int count() 返回出现在 至少一个 区间中的整数个数。
// 注意：区间 [left, right] 表示满足 left <= x <= right 的所有整数 x
// 珂朵莉树
typedef pair<int, int> PII;
class CountIntervals {
   public:
    int ans;
    set<PII> s;
    CountIntervals() {
        s.clear();
        ans = 0;
    }

    void add(int left, int right) {
        auto it = s.lower_bound(PII(left, 0));
        if (it != s.begin()) it = prev(it);
        int L = left, R = right;
        while (it != s.end() and it->first <= right) {
            if (it->second < left) {
                ++it;
                continue;
            }
            L = min(L, it->first);
            R = max(R, it->second);
            ans -= it->second - it->first + 1;
            s.erase(it++);
        }
        ans += R - L + 1;
        s.insert(PII(L, R));
    }

    int count() { return ans; }
};

// L715. Range模块是跟踪数字范围的模块。设计一个数据结构来跟踪表示为 半开区间 的范围并查询它们。

// 半开区间 [left, right) 表示所有 left <= x < right 的实数 x 。

// 实现 RangeModule 类:

// RangeModule() 初始化数据结构的对象。
// void addRange(int left, int right) 添加 半开区间 [left, right)，跟踪该区间中的每个实数。添加与当前跟踪的数字部分重叠的区间时，应当添加在区间 [left,
// right) 中尚未跟踪的任何数字到该区间中。 boolean queryRange(int left, int right) 只有在当前正在跟踪区间 [left, right) 中的每一个实数时，才返回 true
// ，否则返回 false 。 void removeRange(int left, int right) 停止跟踪 半开区间 [left, right) 中当前正在跟踪的每个实数。

// 珂朵莉树
typedef pair<int, int> PII;
class RangeModule {
   public:
    ODT O;
    RangeModule() {
        O.n = 1000000007;
        O.odt.insert({0, 1000000002, 0});
    }

    // [left, right)
    void addRange(int left, int right) { O.assign(left, right - 1, 1); }

    bool queryRange(int left, int right) { return O.check(left, right - 1); }

    void removeRange(int left, int right) { O.assign(left, right - 1, 0); }
};