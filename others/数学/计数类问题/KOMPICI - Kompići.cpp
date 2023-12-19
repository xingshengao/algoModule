// https://www.luogu.com.cn/problem/SP10069
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    vector<int> cnt(1024);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        int t = 0;
        for (int j = 0; j < a.size(); j++) {
            int v = a[j] - '0';
            t |= 1 << v;
        }
        cnt[t]++;
    }
    int res = 0;
    for (int i = 0; i < 1024; i++) {
        res += cnt[i] * (cnt[i] - 1) / 2;
    }
    for (int i = 0; i < 1024; i++) {
        for (int j = i + 1; j < 1024; j++) {
            if (i & j) {
                res += cnt[i] * cnt[j];
            }
        }
    }
    cout << res << endl;
    return 0;
}
