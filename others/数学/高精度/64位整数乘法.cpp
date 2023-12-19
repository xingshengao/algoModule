// https://www.acwing.com/problem/content/description/92/
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int mul(int a, int b, int mod) {    // 返回a * b % mod, a <= 1e18, b <= 1e18, mod <= 1e18
    int res = 0;
    while (b) {
        if (b & 1) {
            res = (res + a) % mod;
        }
        a = a * 2 % mod;
        b >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int a, b, mod;
    cin >> a >> b >> mod;
    cout << mul(a, b, mod) << endl;
    return 0;
}
