#include <bits/stdc++.h>
using namespace std;

// string 分割
vector<string> split(typename string::const_iterator begin, typename string::const_iterator end, char val) {
    vector<string> res;
    string cur = "";
    for (auto it = begin; it != end; it++) {
        if (*it == val) {
            res.push_back(cur);
            cur.clear();
        } else
            cur.push_back(*it);
    }
    res.push_back(cur);
    return res;
}

class Solution {
   public:
    string ReverseString(string s) {
        vector<string> vec = split(s.begin(), s.end(), ' ');
        for (auto& s : vec) {
            reverse(s.begin(), s.end());
        }
        string ans;
        for (int i = 0; i < vec.size() - 1; ++i) {
            ans += vec[i];
            ans += " ";
        }
        ans += vec.back();
        return ans;
    }
};
