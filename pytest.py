import logging
import time
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from math import gcd
from typing import List

from numpy import arange
from tqdm import tqdm

if __name__ == '__main__':
    a = "faddab"
    s = "ab"
    b = a.count(a[1])
    print(b)
