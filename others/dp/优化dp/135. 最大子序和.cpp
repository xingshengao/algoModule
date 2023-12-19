// https://www.acwing.com/problem/content/137/
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    set<tuple<int, int>> s;
    s.insert({0, -1});
    int res = v[0], t = 0;
    for (int i = 0; i < n; i++) {
        t += v[i];
        while (s.size()) {
            auto x = *s.begin();
            int a = get<0> (x), b = get<1> (x);
            if (i - b > k) {
                s.erase(s.begin());
            } else {
                break;
            }
        }
        auto x = *s.begin();
        int a = get<0> (x);
        res = max(res, t - a);
        s.insert({t, i});
    }
    cout << res << endl;
}