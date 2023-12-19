// https://www.luogu.com.cn/problem/P1819
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int dp[200][200][200];
vector<vector<int>> nxta, nxtb, nxtc;
int mod = 1e8;

int dfs(int x, int y, int z) {
    if (dp[x][y][z] != 0) return dp[x][y][z];
    dp[x][y][z]++;
    for (int i = 0; i < 26; i++) {
        if (nxta[x + 1][i] != -1 && nxtb[y + 1][i] != -1 && nxtc[z + 1][i] != -1) {
            dp[x][y][z] += dfs(nxta[x + 1][i], nxtb[y + 1][i], nxtc[z + 1][i]);
            dp[x][y][z] %= mod;
        }
    }
    return dp[x][y][z] % mod;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    string a, b, c;
    cin >> a >> b >> c;
    memset(dp, 0, sizeof dp);
    nxta = vector<vector<int>> (n + 1, vector<int> (26, -1));
    nxtb = vector<vector<int>> (n + 1, vector<int> (26, -1));
    nxtc = vector<vector<int>> (n + 1, vector<int> (26, -1));
    // 求序列自动机
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxta[i][j] = nxta[i + 1][j];
            nxtb[i][j] = nxtb[i + 1][j];
            nxtc[i][j] = nxtc[i + 1][j];
        }
        nxta[i][a[i] - 'a'] = i;
        nxtb[i][b[i] - 'a'] = i;
        nxtc[i][c[i] - 'a'] = i;
    }
    int res = 0;
    for (int i = 0; i < 26; i++) {
        if (nxta[0][i] != -1 && nxtb[0][i] != -1 && nxtc[0][i] != -1) {
            res += dfs(nxta[0][i], nxtb[0][i], nxtc[0][i]);
            res %= mod;
        }
    }
    cout << res << endl;
    return 0;
}
