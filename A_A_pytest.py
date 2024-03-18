import logging
import time
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from math import gcd
from typing import List

from numpy import arange
from tqdm import tqdm

from typing import List
from collections import Counter


class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        mod = 1000000007
        n = len(nums)
        # dfs(i, j) 代表[0: i], 以第i个元素为结尾选出和为j的方法数量

        @cache
        def dfs(i: int, j: int) -> int:
            if i < 0:
                return 0
            if j <= 0:
                return 0
            if i == 0:
                if j == nums[0]:
                    return 1
                else:
                    return 0
            res = 0
            # 选当前元素
            if j >= nums[i]:
                res += dfs(i - 1, j - nums)
                res %= mod
            return res
        ans = 0
        for i in range(0, n):
            ans += dfs(i, k)
            ans %= mod
        return ans
        


if __name__ == '__main__':
    pass
