#include "bits/stdc++.h"
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template <class T>
bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V>& x) {
    cerr << '{';
    __print(x.first);
    cerr << ", ";
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T& x) {
    int f = 0;
    cerr << '{';
    for (auto& i : x) cerr << (f++ ? ", " : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) cerr << ", ";
    _print(v...);
}

const int MOD = 1000000007;
const char nl = '\n';
const int MX = 100001;

class Solution {
   public:
    long long numberOfSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, ordered_set<int>> mp;
        for (int i = 0; i < n; ++i) {
            mp[nums[i]].insert(i);
        }
        // 上一个、下一个更大数字的下标
        vector<int> pre(n, -1), suf(n, n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (st.size() && nums[st.top()] <= nums[i]) st.pop();
            if (st.size()) pre[i] = st.top();
            st.push(i);
        }
        while (st.size()) st.pop();
        for (int i = n - 1; i >= 0; --i) {
            while (st.size() && nums[st.top()] <= nums[i]) st.pop();
            if (st.size()) suf[i] = st.top();
            st.push(i);
        }
        int ans = n;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int L = pre[i], R = suf[i];
            auto s = mp[nums[i]];
            int a = sz(s) - s.order_of_key(L + 1);
            int b = sz(s) - s.order_of_key(R);
            sum += a - b;
            sum--;
        }
        return ans + sum / 2;
    }
};

void solve() {
    int N;
    cin >> N;
    vpl A(N);
    F0R(i, N) cin >> A[i].s >> A[i].f;
    sort(all(A));
    ordered_set<ll> pos;
    ll ans = 0;
    F0R(i, N) {
        ans += sz(pos) - pos.order_of_key(A[i].s);
        pos.ins(A[i].s);
    }
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
