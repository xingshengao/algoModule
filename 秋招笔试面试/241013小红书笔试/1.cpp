#include <bits/stdc++.h>
#define int long long
using namespace std;

#define all(c) c.begin(), c.end()

bool isdig(char x) {
    return x >= '0' && x <= '9';
}
bool isup(char x) {
    return x >= 'A' && x <= 'Z';
}
bool isdown(char x) {
    return x >= 'a' && x <= 'z';
}
bool islet(char x) {
    return isup(x) || isdown(x);
}

void solve() {
    int n, m;
    cin >> n >> m;  // n个评委m个选手
    vector<string> vec(n);
    for (int i = 0; i < n; ++i) cin >> vec[i];
    vector<int> sum(m, 0);  // 总分数
    vector<string> b(m);    // 每个选手的被打分
    for (int i = 0; i < n; ++i) {
        string& s = vec[i];
        for (int j = 0; j < m; ++j) {
            if (isdown(s[j]))
                b[j].push_back(s[j]);
            else if (isup(s[j]))
                b[j].push_back(char('a' + s[j] - 'A'));
        }
    }
    for (int i = 0; i < n; ++i) {
        sort(all(b[i]));
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j + 1 < b[i].size(); ++j) {
            sum[i] += b[i][j] - 'a';
        }
        sum[i] = (sum[i] + n - 3) / (n - 2);
    }
    vector<int> idx(m, 0);
    for (int i = 0; i < m; ++i) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int& i, int& j) {
        if (sum[i] != sum[j]) return sum[i] < sum[j];
        
    });
    for (int i = 0; i < m - 1; ++i) {
        cout << idx[i] + 1 << " ";
    }
    cout << idx[m - 1] + 1 << endl;
    for (int i = 0; i < m - 1; ++i) {
        cout << (char)('a' + sum[idx[i]]) << " ";
    }
    cout << (char)('a' + sum[idx[m - 1]]) << endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}