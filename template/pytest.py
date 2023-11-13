import logging
import time
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from math import gcd
from typing import List
from tqdm import tqdm
from numpy import arange

# 对于字典序最小子序列问题，通常用单调栈解决：从左往右遍历 A, 把A[i]入栈,
#  入栈前把栈中大于A[i]的数字都弹出 这样最后可以得到一字典序最小且递增的序列A[i]
# 的数都弹出。这样最后可以得到一个字典序最小且递增的序列。
# 设mn为满足a[i] = a[0]的b[i]的最小值, 分类讨论
# mn <= a[0], 仅需要保留a[idx_mn] b[idx_mn]两个元素
# mn > a[0], 从去掉>= b[idx]和去掉>b[idx]中选择字典序更小的序列
n = int(input())
A = list(map(int, input().split()))
a, b = [], []
for x, y in zip(A[: n], A[n:]):
    while len(a) and a[-1] > x:
        a.pop()
        b.pop()
    a.append(x)
    b.append(y)

i = bisect_right(a, a[0])
mn = min(b[:i])
if mn < a[0]:
    print(a[0], mn)
    exit()

l = bisect_left(a, b[0])
r = bisect_right(a, b[0])
print(*min(a[:l] + b[:l], a[:r] + b[:r]))


# if __name__ == '__main__':
#     for i in tqdm(range(1000)):
#         time.sleep(0.1)
