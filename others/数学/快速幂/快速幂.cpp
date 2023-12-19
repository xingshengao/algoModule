int pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (long long)res * a % mod;
        }
        a = (long long)a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
