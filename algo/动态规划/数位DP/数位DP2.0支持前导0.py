# 数位DP灵神模板2.0, 支持前导0
from functools import cache


class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        low = str(start)
        high = str(finish)
        n = len(high)
        low = '0' * (n - len(low)) + low # low字符串补足长度
        
        diff = n - len(s)

        @cache
        def dfs(i: int, limit_low: bool, limit_high: bool, is_num: bool) -> int:
            if i == n:
                return 1 if is_num else 0
            
            res = 0
            # 前面填的都是0, limit_low一定是True
            if not is_num and low[i] == '0':
                # 这一位也可以填0
                if i < diff:
                    res += dfs(i + 1, True, False, False)

            # 第 i 个数位可以从哪枚举到哪
            # 如果对数位有其它约束，应当只在下面的 for 循环做限制
            lo = int(low[i]) if limit_low else 0
            hi = int(high[i]) if limit_high else 9

            # 对数位的其它限制, 写在枚举d这边
            d0 = 0 if is_num else 1
            if i < diff:
                for d in range(max(lo, d0), min(hi, limit) + 1):
                    res += dfs(i + 1, limit_low and d == lo, limit_high and d == hi, True)
            else:
                # 必须填 int(s[i-diff])
                x = int(s[i - diff])
                if max(lo, d0) <= x and x <= min(hi, limit):
                    res = dfs(i + 1, limit_low and x == lo, limit_high and x == hi, True)
            return res

        return dfs(0, True, True, False)