#include <bits/stdc++.h>
using namespace std;
void solve1() {  // 01背包+完全背包+多重背包
    // N件物品和一个容量是target背包
    // 物品有三类
    // 第一类物品只能用1次（01背包）；
    // 第二类物品可以用无限次（完全背包）；
    // 第三类物品最多只能用s[i]次(多重背包)
    // 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
    int N, target;
    cin >> N >> target;
    vector<int> W(N), V(N), S(N);  // 体积, 价值, 个数, 0代表无限个, -1代表一个
    for (int i = 0; i < N; ++i) {
        cin >> W[i] >> V[i] >> S[i];
    }
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < N; ++i) {
        if (S[i] == -1) {  // 01背包
            for (int j = target; j >= W[i]; --j) {
                dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
            }
        } else if (S[i] == 0) {  // 完全背包
            for (int j = W[i]; j <= target; ++j) {
                dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
            }
        } else {                                                     // 多重背包
            for (int j = target; j >= W[i]; --j) {                   // 枚举容量
                for (int k = 1; k <= S[i] and k * W[i] <= j; ++k) {  // 枚举几个
                    dp[j] = max(dp[j], dp[j - k * W[i]] + k * V[i]);
                }
            }
        }
    }
    cout << dp[target] << endl;
}
void _solve1() {  // 01背包+完全背包+多重背包, 二进制优化多重背包
    // N件物品和一个容量是target背包
    // 物品有三类
    // 第一类物品只能用1次（01背包）；
    // 第二类物品可以用无限次（完全背包）；
    // 第三类物品最多只能用s[i]次(多重背包)
    // 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
}
void solve2() {
    //  01背包与完全背包的混合
    // 考虑到在01背包和完全背包中给出的伪代码只有一处不同，故如果只有两类物品
    // 一类物品只能取一次，另一类物品可以取无限次，那么只需在对每个物品应用转移方程时，
    // 根据物品的类别选用顺序或逆序的循环即可
}
int main() {
    solve1();
    return 0;
}
