import logging
import time
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from math import gcd
from typing import List

from numpy import arange
from tqdm import tqdm

class Solution_1:
    def maxFrequencyElements(self, nums):
        cnt = dict()
        for x in nums:
            if x in cnt:
                cnt[x] += 1
            else:
                cnt[x] = 1
        m = 0
        for v in cnt.values():
            m = max(m, v)
        ans = 0
        for v in cnt.values():
            if v == m:
                ans += v
        return ans
if __name__ == '__main__':
    pass