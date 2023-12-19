#include <bits/stdc++.h>

using namespace std;

vector<int> palindromic_number(int n) {
    set<int> s;
    for (int left = 0; left <= n; left++) { // 枚举回文数的左半部分
        int p = left;
        for (int x = left; x > 0; x /= 10) p = p * 10 + x % 10;
        s.insert(p);
        p = left / 10;
        for (int x = left; x > 0; x /= 10) p = p * 10 + x % 10;
        s.insert(p);
    }
    return vector<int> (s.begin(), s.end());
}

int main() {
    int n;
    cin >> n;
    vector<int> res = palindromic_number(n);
    for (int x : res) {
        cout << x << ' ';
    }
    return 0;
}
