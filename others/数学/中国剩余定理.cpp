// https://www.luogu.com.cn/problem/P1495
#include <bits/stdc++.h>
#define int long long

using namespace std;

// 给定一系列模数和余数, 求最小正数解
struct CRT {

    int exgcd(int a, int b, int& x, int& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    }

    int inv(int a, int p) {
        int x, y;
        exgcd(a, p, x, y);
        return (x % p + p) % p;
    }

    int get(vector<int>& a, vector<int>& b) {   // a是模数数组, b是余数数组
        int p = 1, x = 0, n = a.size();
        for (int i = 0; i < n; i++) {
            p *= a[i];
        }
        for (int i = 0; i < n; i++) {
            int r = p / a[i];
            x += (b[i] * r * inv(r, a[i])) % p;
        }
        return x % p;
    }
};

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    CRT C;
    cout << C.get(a, b) << endl;
}