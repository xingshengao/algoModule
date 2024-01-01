#include <bits/stdc++.h>
using namespace std;
void solve1() {
    // N件物品和一个容量是target背包。每件物品有S[i]件,物品体积和价值分别为W[i], V[i]
    // 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
    int N, target;
    cin >> N >> target;
    vector<int> W(N), V(N), S(N);  // 体积, 价值, 个数
    for (int i = 0; i < N; ++i) {
        cin >> W[i] >> V[i] >> S[i];  // 体积, 价值, 数量
    }
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < N; ++i) {                                // 枚举物品
        for (int j = target; j >= W[i]; --j) {                   // 枚举容量
            for (int k = 1; k <= S[i] and k * W[i] <= j; ++k) {  // 枚举几个
                dp[j] = max(dp[j], dp[j - k * W[i]] + k * V[i]);
            }
        }
    }
    cout << dp[target] << endl;
}
void solve2() {  // 多重背包二进制优化
    // N件物品和一个容量是target背包。每件物品有S[i]件,物品体积和价值分别为W[i], V[i]
    // 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
    // 二进制优化实际上是对S[i]进行位运算分解, 类似树状数组, 快速幂分解
    // s个拆成log(s)从而优化时间复杂度
    int N, target;
    cin >> N >> target;
    vector<int> W(N), V(N), S(N);  // 体积, 价值, 个数
    for (int i = 0; i < N; ++i) {
        cin >> W[i] >> V[i] >> S[i];  // 体积, 价值, 数量
    }
    vector<int> dp(target + 1);
    typedef pair<int, int> PII;
    vector<PII> goods;  // 存放分解后的物品, (体积, 价值)
    for (int i = 0; i < N; ++i) {
        int w = W[i], v = V[i], s = S[i];  // 体积,价值,个数
        for (int k = 1; k <= s; k <<= 1) {
            s -= k;
            goods.push_back(PII(w * k, v * k));
        }
        if (s > 0) goods.push_back(PII(w * s, v * s));
    }
    // 从而转换为了01背包, 进行处理即可
    for (auto& [w, v] : goods) {
        for (int j = target; j >= w; --j) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
    cout << dp[target] << endl;
}
int main() {
    solve2();
    return 0;
}
