from functools import cache

# 基础版, 不支持前导0
class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        low = str(start)
        high = str(finish)
        n = len(high)
        low = '0' * (n - len(low)) + low # low字符串补足长度
        
        diff = n - len(s)

        @cache
        def dfs(i: int, limit_low: bool, limit_high: bool) -> int:
            if i == n:
                return 1
            # 第 i 个数位可以从哪枚举到哪
            # 如果对数位有其它约束，应当只在下面的 for 循环做限制
            lo = int(low[i]) if limit_low else 0
            hi = int(high[i]) if limit_high else 9

            # 对数位的其它限制, 写在枚举d这边
            res = 0
            if i < diff:
                for d in range(lo, min(hi, limit) + 1):
                    res += dfs(i + 1, limit_low and d == lo, limit_high and d == hi)
            else:
                # 必须填 int(s[i-diff])
                x = int(s[i - diff])
                if lo <= x and x <= min(hi, limit):
                    res = dfs(i + 1, limit_low and x == lo, limit_high and x == hi)
            return res

        return dfs(0, True, True)