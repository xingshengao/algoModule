#include <bits/stdc++.h>

using namespace std;

vector<int> divide(int n) {
    vector<int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            res.push_back(i);
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

signed main() {
    int n;
    cin >> n;
    vector<int> res = divide(n);
    for (int x : res) cout << x << ' ';
}