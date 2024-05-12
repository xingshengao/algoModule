#include <bits/stdc++.h>
#define int long long
using namespace std;
std::vector<int> kmp(std::string& text, std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m);
    int c = 0;
    for (int i = 1; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        pi[i] = c;
    }

    std::vector<int> res;
    c = 0;
    for (int i = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        if (c == m) {
            res.push_back(i - m + 1);
            c = pi[c - 1];
        }
    }
    return res;
}
void solve() {
    // 旋转实际上就是左移操作
    vector<string> vec;
    string s0;
    while (std::getline(std::cin, s0)) {
        if (s0.empty()) break;
        vec.push_back(s0);
        // t去除空格
    }
    for (int i = 0; i < vec.size(); i += 2) {
        // 固定长度滑动窗口
        string& s = vec[i];
        string& t = vec[i + 1];
        string ss = s + s;
        auto r = kmp(ss, t);
        if (r.size() > 0) {
            cout << "1";
        } else
            cout << "0";
    }
    cout << endl;
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