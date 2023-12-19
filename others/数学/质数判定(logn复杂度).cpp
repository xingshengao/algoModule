// https://loj.ac/p/143
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;


struct isPrime {

    vector<long long> a = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    isPrime() {}

    long long pow(long long a, long long b, long long mod) {
        long long res = 1;
        while (b) {
            if (b & 1) {
                res = (__int128)res * a % mod;
            }
            a = (__int128)a * a % mod;
            b >>= 1;
        }
        return res % mod;
    }

    bool check(long long n) {
        if (n == 1) return 0;
        for (int i = 0; i < 10; i++) {
            if (a[i] == n) return 1;
            if (pow(a[i], n - 1, n) != 1) return 0;
            for (long long j = n - 1, v; j % 2 == 0;) {
                if ((v = pow(a[i], j /= 2, n)) == n - 1) break;
                if (v != 1) return 0;
            }
        }
        return 1;
    }

};

signed main() {
    long long n;
    isPrime C;
    while (scanf("%lld", &n) != EOF) {
        puts(C.check(n) ? "Y" : "N");
    }
}