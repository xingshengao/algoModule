#include <bits/stdc++.h>
#define int long long
using namespace std;

bool isValid(string& s) {
    for (char& c : s) {
        if (!(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')) return false;
    }
    return true;
}
void solve() {
    vector<string> vec;
    vector<string> A, B;
    set<string> S;  // 合法的去重
    string t;
    while (std::getline(std::cin, t)) {
        if (t.empty()) break;
        // t去除空格
        string s;
        for (char& c : t) if (c != ' ' && c != '\n' && c != '\t') s.push_back(c);        
        if (!isValid(s)) {
            B.push_back(s);
        } else {
            if (!S.count(s)) {
                S.insert(s);
                A.push_back(s);
            }
        }
    }
    // debug(A);
    // debug(B);
    // // 第一行合法
    for (int i = 0; i + 1 < A.size(); ++i) {
        cout << A[i] << " ";
    }
    cout << A.back() << endl;
    // 第二行非法
    for (int i = 0; i + 1 < B.size(); ++i) {
        cout << B[i] << " ";
    }
    cout << B.back() << endl;
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