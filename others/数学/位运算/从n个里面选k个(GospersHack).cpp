// from : https://zhuanlan.zhihu.com/p/360512296
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

void GospersHack(int k, int n)
{
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    while (cur < limit)
    {
        // do something
        int lb = cur & -cur;
        int r = cur + lb;
        cur = (((r ^ cur) >> 2) / lb) | r;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);

    return 0;
}
