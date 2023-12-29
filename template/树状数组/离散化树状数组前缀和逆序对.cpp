#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

void solve() {
    int n;
    cin >> n;
    vector<PII> vec(n);
    vector<int> XX;  // 要离散化的x坐标
    // 输入n个点
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].first >> vec[i].second;
        XX.push_back(vec[i].first);
    }
    // 要求对于所有点来说, yi > y 的 xi < x一共有多少个

    // 要进行树状数组前缀和的点去重
    auto Uni = [](vector<int>& A) -> vector<int> {
        vector<int> ans(A);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };
    // 要进行离散化的数组, 可以是x可以是y
    vector<int> A = Uni(XX);
    // 离散化
    map<int, int> mp;
    for (int i = 0; i < A.size(); ++i) {
        mp[A[i]] = i + 1;
    }
    // 树状数组板子
    vector<int> tr(A.size() + 1, 0);
    auto low_bit = [&](int x) { return x & (-x); };
    auto query = [&](int pos) {
        int sum = 0;
        for (; pos; pos -= low_bit(pos)) sum += tr[pos];
        return sum;
    };
    auto update = [&](int pos, int v) {
        for (; pos < tr.size(); pos += low_bit(pos)) tr[pos] += v;
    };
    // 按照y降序排序
    sort(vec.begin(), vec.end(), [](const PII& a, const PII& b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    // 本题的计算
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = vec[i].first, y = vec[i].second;
        int x_id = mp[x];  // 离散化的编号
        update(x_id, 1);
        ans += query(x_id - 1);  // 比其小的前缀和
    }
    cout << ans << endl;
}
int main() {
    solve();
    return 0;
}