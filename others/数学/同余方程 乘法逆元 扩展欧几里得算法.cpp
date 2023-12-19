// https://www.luogu.com.cn/problem/P1082
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

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
    int a, m, x, y;
    cin >> a >> m;
    exgcd(a, m, x, y);
    cout << ((x % m) + m) % m << endl;

    return 0;
}