#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 如果 N = p1^c1 * p2^c2 * ... *pk^ck
// 约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)
// 约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)

int divisor_cnt(int n) {
    unordered_map<int, int> primes;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if (n > 1) primes[n]++;
    int res = 1;
    for (auto x : primes) {
        res = res * (x.second + 1);
    }
    return res;
}

int divisor_sum(int n) {
    unordered_map<int, int> primes;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if (n > 1) primes[n]++;
    int res = 1;
    for (auto x : primes) {
        int t = 0, p = x.first, cnt = x.second;
        for (int i = 0; i <= cnt; i++) {
            t += pow(p, i);
        }
        res *= t;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    cout << divisor_cnt(n) << ' ' << divisor_sum(n) << endl;
    return 0;
}
