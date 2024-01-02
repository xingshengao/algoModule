#include <bits/stdc++.h>
using namespace std;

// 分组背包问题
// 现有N组物品和一个最多能承重M的背包, 每组物品有若干个m,同一组内的物品最多只能选一个。
// 每件物品的重量是W[i][j], 价值是V[i][j], 其中i是组号, j是组内编号
// 在背包能承受的范围m内,试问将哪些物品装入背包后可使总价值最大m,求这个最大价值
void solve() {
    int N, target;  // 组的数量, 背包体积
    cin >> N >> target;
    vector W(N + 10, vector<int>(110, 0));  // 体积
    vector V(N + 10, vector<int>(110, 0));  // 价值
    vector<int> S(N + 10);                  // 每组有几个

    for (int i = 0; i < N; ++i) {
        cin >> S[i];
        for (int j = 0; j < S[i]; ++j) {
            cin >> W[i][j] >> V[i][j];
        }
    }
    vector<int> dp(target + 1, 0);

    for (int i = 0; i < N; ++i) {             // 枚举哪一组
        for (int j = target; j >= 1; --j) {   // 倒着枚举容量
            for (int k = 0; k < S[i]; ++k) {  // 枚举一组内选哪个
                if (j >= W[i][k]) {
                    dp[j] = max(dp[j], dp[j - W[i][k]] + V[i][k]);
                }
            }
        }
    }

    cout << dp[target] << endl;
}
int main() {
    solve();
    return 0;
}