'''
Sorted Containers是Apache2许可的sorted collections库

它是用纯Python编写的，并且可以像C扩展一样快速。
'''
from sortedcontainers import SortedList
s = SortedList([1,2,3])
# 添加元素
s.add(23)
s.add(7)
s.add(3)
print(s)

s = SortedList([1,2,3])
# 删除元素，如果不存在，不报错
s.discard(7)
print(s)
'''
删除元素，如果不存在，会报错
s.remove(24)
print(s)
pop 删除并返回索引处的值
bisect_left 返回索引值
count 返回值出现的次数
index 返回第一个值处的索引
'''
#有序字典
#setdefault 添加键值对
from sortedcontainers import SortedDict
sd = SortedDict()
sd.setdefault('a', 1)
sd.setdefault('b', 12)
sd.setdefault('b', 10)
sd.pop('b')
sd.get('a')
print(sd)

#有序不重复集合
from sortedcontainers import SortedSet
ss = SortedSet()
ss.add(3)
ss.add(1)
ss.add(2)
ss.add(2)
print(ss)
from sortedcontainers import SortedSet
ss = SortedSet([1, 2, 3, 4, 5])
ss.discard(5)
ss.discard(0)
print(ss)
from sortedcontainers import SortedSet
ss = SortedSet('abcde')
ss.pop()
ss.pop(2)
print(ss)
from sortedcontainers import SortedSet
ss = SortedSet([1, 2, 3, 4, 5])
ss.remove(5)
print(ss == set([1, 2, 3, 4]))
