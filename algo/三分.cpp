#include <bits/stdc++.h>
#define int long long
using namespace std;

// 如果需要求出单峰函数的极值点，通常使用二分法衍生出的三分法求单峰函数的极值点。
// 三分法与二分法的基本思想类似，但每次操作需在当前区间[l, r]（下图中除去虚线范围内的部分）内任取两点 lmid, rmid
// 如果 f(lmid) < f(rmid)，则在[rmid, r]（下图中的红色部分）中函数必然单调递增，
// 最小值所在点（下图中的绿点）必然不在这一区间内，可舍去这一区间。反之亦然。

// 三分伪代码
// while (r - l > eps) {
//   mid = (l + r) / 2;
//   lmid = mid - eps;
//   rmid = mid + eps;
//   if (f(lmid) < f(rmid))
//     r = mid;
//   else
//     l = mid;
// }

// 例题
// http://codeforces.com/problemset/problem/439/D
// 给两个数组 a 和 b，长度均不超过 1e5，元素范围为 [1,1e9]。
// 每次操作可以使 a 或 b 中的任意元素 +1 或 -1，求使 min(a) >= max(b) 的最小操作次数。

// 函数图像是开口向上抛物线的三分写法
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // 计算代价, 使得min(a) >= x and max(b) <= x
    function<int(int)> calc = [&](int x) -> int {
        int res = 0;
        for (int v : a) {
            if (v < x) {
                res += x - v;
            }
        }
        for (int v : b) {
            if (v > x) {
                res += v - x;
            }
        }
        return res;
    };
    int l = 0, r = 1e18;

    // // 写法1, 抄的cf大佬的
    // while (l < r) {
    //     int m1 = (l + l + r) / 3, m2 = (l + r + r) / 3;
    //     if (calc(m1) > calc(m2)) { // 舍去左边这一段
    //         l = m1 + (l == m1);
    //     } else { // 舍去右边这一段
    //         r = m2 - (r == m2);
    //     }
    // }

    // 写法2
    while (l + 3 <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (calc(m1) < calc(m2)) {  // lmid < rmid, 舍去右边这一段
            r = m2;
        } else {  // lmid > rmid, 舍去左边这一段
            l = m1;
        }
    }
    // 最终函数极小值点在区间[l, r]之间
    int ans = 1e18;
    for (int x = l; x <= r; ++x) {
        ans = min(ans, calc(x));
    }
    cout << ans << endl;
}

// 补充一个开口向下, 求最大值的写法
void solve_() {
    int l = 0, r = 1e18;

    function<int(int)> calc = [&](int x) -> int { return 1; };

    while (l + 3 <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (calc(m1) < calc(m2)) {  // lmid < rmid, 舍去左边这一段
            l = m1;
        } else {  // lmid > rmid, 舍去右边这一段
            r = m2;
        }
    }

    // 最终极大值点在[l, r]之间
    int ans = -1e18;
    for (int x = l; x <= r; ++r) {
        ans = max(ans, calc(x));
    }

    cout << ans << endl;
}