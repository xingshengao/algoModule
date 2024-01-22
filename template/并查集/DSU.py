from typing import List

class DSU:
    def __init__(self, n):
        self.p = list(range(n))
        self.sz = [1] * n

    def find(self, x):
        if self.p[x] != x:
            self.p[x] = self.find(self.p[x])
        return self.p[x]

    def merge(self, x, y):
        xr = self.find(x)
        yr = self.find(y)
        if xr != yr:
            self.p[xr] = yr
            self.sz[yr] += self.sz[xr]

    def size(self, x):
        return self.sz[self.find(x)]