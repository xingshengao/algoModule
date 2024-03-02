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
    def maxOperations(self, nums: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(l: int, r: int, v: int) -> int:
            if l >= r:
                return 0
            res = 0
            if nums[l] + nums[l + 1] == v:
                res = max(res, dfs(l + 2, r) + 1)
            if nums[r] + nums[r - 1] == v:
                res = max(res, dfs(l, r - 2))
            if nums[r] + nums[l] == v:
                res = max(res, dfs(l + 1, r - 1))
            return res

        ans = 0
        res1 = dfs(1, n - 2, nums[-1] + nums[0])
        res2 = dfs(0, n - 3, nums[-1] + nums[-2])
        res3 = dfs(2, n - 1, nums[0] + nums[1])
        ans = max(res1 + 1, res2 + 1, res3 + 1)


if __name__ == '__main__':
    pass
