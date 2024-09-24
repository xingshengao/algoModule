#include <bits/stdc++.h>
#define int long long
using namespace std;

using PII = pair<int, int>;

void solve() {
    int n;
    cin >> n;
    vector<PII> vec(n);
    for (int i = 0; i < n; ++i) cin >> vec[i].first >> vec[i].second;
    sort(vec.begin(), vec.end(), [&](const auto&a, const auto&b) {
        return a.first < b.first;
    });
    vector<int> lis;
    for (int i = 0; i < n; ++i) {
       auto it = upper_bound(lis.begin(), lis.end(), vec[i].second);
       if (it == lis.end()) lis.push_back(vec[i].second);
       else *it = vec[i].second; 
       
    }
    cout << n - lis.size() << endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}