// https://www.luogu.com.cn/problem/CF1073E
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int l, r, k;
pair<int, int> dp[20][1 << 11][2][2];
int mod = 998244353;
vector<int> p10(19);

int calc(int x) {
    int res = 0;
    while (x) {
        res += x % 2;
        x /= 2;
    }
    return res;
}

pair<int, int> dfs(int pos, int mask, bool limit, bool full, string& s) {
    if (dp[pos][mask][limit][full].first != -1 && dp[pos][mask][limit][full].second != -1) return dp[pos][mask][limit][full];
    if (pos == s.size()) {
        if (full && calc(mask) <= k) return {0, 1};
        else return {0, 0};
    }
    pair<int, int> res = {0, 0};
    if (!full) res = dfs(pos + 1, mask, false, false, s);
    int now = s[pos] - '0';
    int down = full ? 0 : 1;
    int up = limit ? now : 9;
    int n = s.size();
    for (int i = down; i <= up; i++) {
        pair<int, int> nxt = dfs(pos + 1, mask | (1 << i), limit && (i == now), true, s);
        res = {(nxt.second * p10[n - pos - 1] % mod * i % mod + nxt.first + res.first) % mod, (res.second + nxt.second) % mod};
    }
    return dp[pos][mask][limit][full] = res;
}

void init() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < (1 << 11); j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    dp[i][j][k][l].first = -1;
                    dp[i][j][k][l].second = -1;
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    cin >> l >> r >> k;
    p10[0] = 1;
    for (int i = 1; i <= 18; i++) {
        p10[i] = p10[i - 1] * 10 % mod;
    }
    string sl = to_string(l - 1), sr = to_string(r);
    init();
    pair<int, int> resl = dfs(0, 0, true, false, sl);
    init();
    pair<int, int> resr = dfs(0, 0, true, false, sr);
    cout << ((resr.first - resl.first) % mod + mod) % mod << endl;
    return 0;
}