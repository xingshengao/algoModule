// https://www.luogu.com.cn/problem/CF7C
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 常用于求 ax + by + c = 0 的一组可行解
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int a, b, c, x, y;
    cin >> a >> b >> c;
    int d = exgcd(a, b, x, y);
    if (c % d == 0) {   // 有解
        cout << -c / d * x << ' ' << -c / d * y << endl;
    } else {    // 无解
        cout << -1 << endl;
    }
    return 0;
}
