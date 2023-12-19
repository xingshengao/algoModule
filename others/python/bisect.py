​
Python自带的一个二分库，列表有序时使用

导入
import bisect

找到第一个大于等于x的数的位置
>>> a = [1, 2, 2, 2, 3]
>>> pos = bisect.bisect_left(a, 2)
>>> pos
1
>>> a[pos]
2

找到第一个大于x的数的位置
>>> a = [1, 2, 2, 2, 3]
>>> pos = bisect.bisect_right(a, 2)
>>> pos
4
>>> a[pos]
3

计算数组里有多少个x
>>> a = [1, 2, 2, 2, 3]
>>> bisect.bisect_right(a, 2) - bisect.bisect_left(a, 2)
3

在有序列表里插入元素
# 查找插入位置时间复杂度O(logn), 插入元素时间复杂度O(n)
>>> a = [1, 2, 2, 2, 4]
>>> bisect.insort(a, 3)
>>> a
[1, 2, 2, 2, 3, 4]


​