// https://www.luogu.com.cn/problem/AT_abc194_f
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

string s;
int k, mod = 1e9 + 7;;
vector<int> v;

int dp[200005][20][2][2];

int dfs(int pos, int st, bool limit, bool full) {
    int cnt = __builtin_popcount(st);
    if (dp[pos][cnt][limit][full] != -1) return dp[pos][cnt][limit][full];
    if (pos == s.size()) return full && cnt == k;
    int res = 0;
    if (!full) res += dfs(pos + 1, cnt, false, false);
    int now = v[pos];
    int down = full ? 0 : 1;
    int up = limit ? now : 15;
    for (int i = down; i <= up; i++) {
        res += dfs(pos + 1, st | (1 << i), limit && (i == now), true);
        res %= mod;
    }
    return dp[pos][cnt][limit][full] = res;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    cin >> s >> k;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if ('A' <= s[i] && s[i] <= 'F') {
            v.push_back(s[i] - 'A' + 10);
        } else {
            v.push_back(s[i] - '0');
        }
    }
    memset(dp, -1, sizeof dp);
    cout << dfs(0, 0, true, false) % mod << endl;
    return 0;
}