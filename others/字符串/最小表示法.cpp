// https://www.luogu.com.cn/problem/P1368
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 最小表示法就是找出字符串S的循环同构串中字典序最小的一个

vector<int> get_min(vector<int>& s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        s.push_back(s[i]);
    }
    int i = 0, j = 1, k = 0;
    while (i < n && j < n) {
        k = 0;
        while (k < n && s[i + k] == s[j + k]) {
            k++;
        }
        if (s[i + k] > s[j + k]) {
            i = i + k + 1;
        } else {
            j = j + k + 1;
        }
        if (i == j) {
            j++;
        }
    }
    vector<int> res;
    for (int j = 0; j < n; j++) {
        res.push_back(s[i + j]);
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
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    v = get_min(v);
    for (int i = 0; i < n; i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
    return 0;
}
