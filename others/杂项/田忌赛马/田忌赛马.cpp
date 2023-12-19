// https://www.luogu.com.cn/problem/P1650
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 1、先降序排序；
// 2、然后将田忌最大的马与国王进行比较；
// 3、如果田忌最大的马大于国王，那么就胜场++；
// 4、如果田忌最大的马小于国王，那么就一定会输，所以用田忌最小的马输给国王最大的马；
// 5、如果田忌最大的马等于国王，那么就比较最小的马；
// 5.1、如果田忌最小的马大于国王最小的马，那么胜场++；
// 5.2、如果田忌最小的马小于国王最小的马，那么用田忌最小的马输给国王最大的马；
// 5.3、如果田忌最小的马等于国王最小的马，就用田忌最小的马对国王最大的马，如果国王最大的马大，那么财产要减200；

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    int l1 = 0, r1 = n - 1, l2 = 0, r2 = n - 1;
    int res = 0;
    while (l1 <= r1) {
        if (a[l1] > b[l2]) {
            res++;
            l1++;
            l2++;
        } else if (a[l1] < b[l2]) {
            res--;
            r1--;
            l2++;
        } else {
            if (a[r1] > b[r2]) {
                res++;
                r1--;
                r2--;
            } else if (a[r1] < b[r2]) {
                res--;
                r1--;
                l2++;
            } else {
                if (a[r1] < b[l2]) {
                    res--;
                }
                r1--;
                l2++;
            }
        }
    }
    cout << res * 200 << endl;
    return 0;
}