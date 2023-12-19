// https://www.luogu.com.cn/problem/P3369
#include <bits/stdc++.h>

using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
// 平衡树
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// rb_tree_tag: 红黑树, splay_tree_tag: splay树
// 插入元素会去重，如果想实现multiset可以使用pair<T, int>，额外增加一个时间维度
// ordered_set tr
// tr.insert(x) 插入
// tr.erase(x) 删除
// tr.order_of_key(x)  x元素的排名 (0-indexed)
// tr.find_by_order(k) 第k大的元素的迭代器 (0-indexed)
// tr.lower_bound(x) >=x 最小元素的迭代器
// tr.upper_bound(x) >x 最小元素的迭代器
// tr1.join(tr2) 合并 (需要保证tr1与tr2不相交)
// tr1.split(x, tr2) 分裂，<=x的元素属于tr1, >x的元素属于tr2
// tr.empty() 返回是否为空
// tr.size() 返回大小
// tr1.swap(tr2) 交换tr1, tr2 O(1)

signed main() {
    int n;
    cin >> n;
    ordered_set<pair<int, int>> tr;
    int cnt = 0, mi = -2e9, ma = 2e9;
    tr.insert({mi, cnt++}); // 因为题目下标从1开始
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {          // 插入一个整数 x
            tr.insert({x, cnt++});
        } else if (op == 2) {   // 删除一个整数 x（若有多个相同的数，只删除一个）
            auto it = tr.lower_bound({x, mi});
            tr.erase(it);
        } else if (op == 3) {   // 查询整数 x 的排名（排名定义为比当前数小的数的个数 + 1）
            auto it = *--tr.lower_bound({x, mi});
            int pos = tr.order_of_key(it) + 1;
            cout << pos << endl;
        } else if (op == 4) {   // 查询排名为 x 的数（如果不存在，则认为是排名小于 x 的最大数。保证 x 不会超过当前数据结构中数的总数）
            auto it = *tr.find_by_order(x);
            cout << it.first << endl;
        } else if (op == 5) {   // 求 x 的前驱（前驱定义为小于 x，且最大的数）
            auto it = *--tr.lower_bound({x, mi});
            cout << it.first << endl;
        } else {                // 求 x 的后继（后继定义为大于 x，且最小的数）
            auto it = *tr.upper_bound({x, ma});
            cout << it.first << endl;
        }
    }
}