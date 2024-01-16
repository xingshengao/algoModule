#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<vector<T>> split(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end, T val) {
    vector<vector<T>> res;
    vector<T> cur;
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
