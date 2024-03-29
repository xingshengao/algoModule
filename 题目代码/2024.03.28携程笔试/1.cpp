#include <iostream>
using namespace std;

int main() {
   int n;
   cin >> n;
   string s = "you", t = "uoy";
   int flag = 1;
   string ans = "";
   for (int i = 0; i < n; ++i) {
    if (flag) {
        ans += s;
    } else {
        ans += t;
    }
    flag ^= 1;
   }
   cout << ans << endl;
}
// 64 位输出请用 printf("%lld")