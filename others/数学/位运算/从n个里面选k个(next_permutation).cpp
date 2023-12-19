#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> v;
    for (int i = 0; i < n - k; i++) {
        v.push_back(0);
    }
    for (int i = 0; i < k; i++) {
        v.push_back(1);
    }
    do {
        for (int i = 0; i < n; i++) {
            cout << v[i];
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
    return 0;
}
