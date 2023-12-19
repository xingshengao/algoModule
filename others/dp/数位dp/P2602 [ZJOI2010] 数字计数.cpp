// https://www.luogu.com.cn/problem/P2602
#include <bits/stdc++.h>
#define int long long

using namespace std;

int dp[44][2][2][44];

int dfs(int pos, bool limit, bool full, string& s, int num, int cnt) {
    if (dp[pos][limit][full][cnt] != -1) return dp[pos][limit][full][cnt];
    if (pos == s.size()) return cnt;
    int res = 0;
    if (!full) res += dfs(pos + 1, false, false, s, num, cnt);
    int now = s[pos] - '0';
    int down = full ? 0 : 1;
    int up = limit ? now : 9;
    for (int i = down; i <= up; i++) {
        res += dfs(pos + 1, limit && (i == now), true, s, num, cnt + (i == num));
    }
    return dp[pos][limit][full][cnt] = res;
}

signed main() {
    int a, b;
    cin >> a >> b;
    string sa = to_string(a - 1), sb = to_string(b);
    vector<int> va, vb;
    for (int i = 0; i <= 9; i++) {
        memset(dp, -1, sizeof dp);
        int resa = dfs(0, true, false, sa, i, 0);
        memset(dp, -1, sizeof dp);
        int resb = dfs(0, true, false, sb, i, 0);
        cout << resb - resa << ' ';
    }
}