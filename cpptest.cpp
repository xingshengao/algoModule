#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
vector<pair<int, int>> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
vector<pair<int, int>> dirs4 = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
long long fpow(long long x, long long exp, long long mod) {  // 快速幂
    long long res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

long long fpow(long long x, long long exp) {  // 快速幂
    long long res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x;
        x = x * x;
    }
    return res;
}

// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode(int x) : val(x), next(NULL) {}
// };
// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
// };

template <typename T>
ostream& operator<<(ostream& out, const set<T>& obj) {
    out << "set(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const unordered_set<T>& obj) {
    out << "unordered_set(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const map<T1, T2>& obj) {
    out << "map(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << it->first << ": " << it->second;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const unordered_map<T1, T2>& obj) {
    out << "unordered_map(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << it->first << ": " << it->second;
    out << ")";
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& obj) {
    out << "<" << obj.first << ", " << obj.second << ">";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& obj) {
    out << "vector(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}

string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() {
    cout << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << " " << to_string(H);
    debug_out(T...);
}

template <typename T>
void mydebug(const char* format, T t) {
    cout << format << "=" << to_string(t) << endl;
}

template <typename Head, typename... Tail>
void mydebug(const char* format, Head H, Tail... T) {
    while (*format != ',') cout << *format++;
    cout << "=" << to_string(H) << ",";
    mydebug(format + 1, T...);
}
#define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)

#define all(c) c.begin(), c.end()
#define REP(i, a, b) for (int i = a; i < (b); i++)
#define RREP(i, a, b) for (int i = a; i >= b; i--)
using LL = long long;
using VI = vector<int>;
using VL = vector<LL>;
using VVI = vector<vector<int>>;
using VVL = vector<vector<LL>>;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<LL, LL, LL>;
using VPII = vector<PII>;

template <class T>
void mkuni(vector<T>& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

template <class T, class S = T>
S SUM(const vector<T>& a) {
    return accumulate(a.begin(), a.end(), S(0));
}

template <class T>
T MAX(const vector<T>& a) {
    return *max_element(a.begin(), a.end());
}

template <class T>
T MIN(const vector<T>& a) {
    return *min_element(a.begin(), a.end());
}

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)

template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
static constexpr long long mod = 1e9 + 7;
using LL = long long;

int main() {
    // Solution so;
    return 0;
}