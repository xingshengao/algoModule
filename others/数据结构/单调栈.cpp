// https://www.luogu.com.cn/problem/P5788
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n + 1), res(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        while (st.size() && v[st.back()] < v[i]) {
            res[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}