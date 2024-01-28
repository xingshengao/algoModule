## 个人代码模板仓库
**Xsa_DeleteMemo**


### 二进制笔记
`__builtin_popcount(int x)` 统计1的数量 `__builtin_popcountll(LL x)`

`__builtin_ctz(int x)` 后缀0的个数, `__builtin_ctzll(LL x)`

`__builtin_clz(int x)` 从最高位开始连续0的个数, 可以用来计算二进制长度(`32 - __builtin_clz(int x)`, `64 - __builtin_clzll(LL x)`)


`二进制加法器a + b = (a ^ b) + 2 * (a & b)`

一个字母大小写的ascii码, 低五位是相同的, `a & 31 == A & 31`; 不同字母的后五位不同