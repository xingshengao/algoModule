// 例题:https://www.luogu.com.cn/problem/P3383
#include <bits/stdc++.h>

using namespace std;
 
vector<int> Eratosthenes(int n) {  // 埃氏筛,时间复杂度O(nloglogn)
    vector<int> prime;
    vector<bool> isPrime(n + 1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            prime.push_back(i);
            for (int j = 2 * i; j <= n; j += i) isPrime[j] = 0;
        }
    }
    return prime;
}

vector<int> Euler(int n) {  // 欧拉筛,时间复杂度O(n)
    vector<int> prime;
    vector<bool> isPrime(n + 1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0) break;
        }
    }
    return prime;
}

int main() {
    int n, q;
    cin >> n >> q;
    // vector<int> prime = Eratosthenes(n);
    vector<int> prime = Euler(n);
    while (q--) {
        int k;
        cin >> k;
        cout << prime[k - 1] << endl;
    }
    return 0;
}
