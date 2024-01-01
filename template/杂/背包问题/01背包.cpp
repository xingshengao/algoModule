#include <bits/stdc++.h>
using namespace std;
void solve1() {
    // N件物品和一个容量是target背包。每件物品只能使用一次。物品体积和价值分别为W[i], V[i]
    // 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
    int N, target;
    cin >> N >> target;
    vector<int> W(N), V(N);  // 体积, 价值
    for (int i = 0; i < N; ++i) {
        cin >> W[i] >> V[i];
    }
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = target; j >= W[i]; --j) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    cout << dp[target] << endl;
}

int main() {
    solve1();
    return 0;
}
