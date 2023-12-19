// https://www.luogu.com.cn/problem/P6218
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int dp[44][44][44][2][2];

int dfs(int pos, int cnt0, int cnt1, bool limit, bool full, string& s) {
    if (dp[pos][cnt0][cnt1][limit][full] != -1) return dp[pos][cnt0][cnt1][limit][full];
    if (pos == s.size()) return full && cnt0 >= cnt1;
    int res = 0;
    if (!full) res += dfs(pos + 1, cnt0, cnt1, false, false, s);
    int now = s[pos] - '0';
    int down = full ? 0 : 1;
    int up = limit ? now : 1;
    for (int i = down; i <= up; i++) {
        res += dfs(pos + 1, cnt0 + (i == 0), cnt1 + (i == 1), limit && (i == now), true, s);
    }
    return dp[pos][cnt0][cnt1][limit][full] = res;
}

string get(int x) {
    string res;
    while (x) {
        res += '0' + (x % 2);
        x /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int a, b;
    cin >> a >> b;
    string sa = get(a - 1), sb = get(b);
    memset(dp, -1, sizeof dp);
    int resa = dfs(0, 0, 0, true, false, sa);
    memset(dp, -1, sizeof dp);
    int resb = dfs(0, 0, 0, true, false, sb);
    cout << resb - resa << endl;
    return 0;
}
