​
导入
import collections

1、计数器Counter
c = collections.Counter('nreyong')

print(c.items()) #打印键、值

print(c.keys()) #打印键

print(c.values()) #打印值

print(c.pop('a')) #删除键'a'并将值带回

c.clear() #清空c

d = collections.Counter('Python')

c.update(d) #将d中的值加到c上

c.update('abc')

del c['b'] #删除key为b的记录

for i in "nreyong": #添加元素
    c[i] += 1

print(c.most_common(n)) #出现最多的n组数

print(sorted(c.elements())) #排序后打印c中元素

c = collections.Counter(a = 3, b = 1)
d = collections.Counter(a = 1, b = 2)

print(c + d)                       # 相加
#Counter({'a': 4, 'b': 3})
print(c - d)                       # 相减，如果小于等于0，删去
#Counter({'a': 2})
print(c & d)                       # 求最小
#Counter({'a': 1, 'b': 1})
print(c | d)                       # 求最大
#Counter({'a': 3, 'b': 2})

2、默认字典defaultdict
import collections

d1 = collections.defaultdict(int)
d2 = collections.defaultdict(set)
d3 = collections.defaultdict(str)
d4 = collections.defaultdict(list)

print(d1[0])
print(d2[0])
print(d3[0])
print(d4[0])

''' 
输出:
0
set()

[]
'''

3、双端队列deque
import collections

# 创建
d = collections.deque()

# 右边添加
d.append('a')

# 左边添加
d.appendleft('b') # 在最左边添加一个元素，此时 d=deque(['b', 'a'])

# 右边添加列表中所有元素
d.extend(['c','d'])

# 左边添加列表中所有元素
d.extendleft(['e','f'])

# 弹出最右边元素
d.pop()

# 弹出最左边元素
d.popleft()

# 将最左边两个元素弹出并加到末尾（想想填正数会怎么样）
d.rotate(-2)

# 计数
d.count('a')

# 删除队列中的元素'c'
d.remove('c')

# 翻转
d.reverse()


​