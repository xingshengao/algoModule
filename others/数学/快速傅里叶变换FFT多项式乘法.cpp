// https://www.luogu.com.cn/problem/P3803
#include <bits/stdc++.h>

using namespace std;

#define complex complex<double>
#define PI acos(-1)

void FFT(vector<complex>& A, int n, int op) {
    if (n == 1) return;
    vector<complex> A1(n / 2), A2(n / 2);
    for (int i = 0; i < n / 2; i++) {
        A1[i] = A[i * 2], A2[i] = A[i * 2 + 1];
    }
    FFT(A1, n / 2, op);
    FFT(A2, n / 2, op);
    complex w1({cos(2 * PI / n), sin(2 * PI / n) * op});
    complex wk({1, 0});
    for (int i = 0; i < n / 2; i++) {
        A[i] = A1[i] + A2[i] * wk;
        A[i + n / 2] = A1[i] - A2[i] * wk;
        wk = wk * w1;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<complex> A(4000000), B(4000000);
    for (int i = 0; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> B[i];
    }
    // 求n
    for (m = n + m, n = 1; n <= m; n <<= 1);
    // 求点值
    FFT(A, n, 1);
    FFT(B, n, 1);
    // 乘积
    for (int i = 0; i < n; i++) {
        A[i] = A[i] * B[i];
    }
    // 求系数
    FFT(A, n, -1);
    // 浮动数计算有误差, 例如[5.999998 + 0.5] = 6
    for (int i = 0; i <= m; i++) {
        cout << (int)(A[i].real() / n + 0.5) << ' ';
    } 
}