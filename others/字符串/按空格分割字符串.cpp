#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s) {
    s += ' ';
    vector<string> res;
    string t;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            res.push_back(t);
            t.clear();
        } else {
            t += s[i];
        }
    }
    return res;
}

signed main() {
    string s = "abc de f";
    vector<string> res = split(s);
    for (string s : res) {
        cout << s << endl;
    }
}