​
1、导入库
import heapq

2、初始化
法一：

nums = [1, 3, 2, 5]
q = []
for i in nums:
	heapq.heappush(q, i)

法二：

q = nums[:]
heapq.heapify(q)

3、依次输出堆顶元素
while q:
	print(heapq.heappop(q))

4、访问堆顶元素并替换之
heapq.heapreplace(q, x)

5、获取最大n个/最小n个元素
maxn = heapq.nlargest(n, q)
minn = heapq.nsmallest(n, q)

6、自定义排序
列表默认按照第一个元素的大小排序，故自定义排序时，可以将基准元素放在第一个位置，优先级越低的元素在列表中的位置应越靠后

d1 = [5, 3, 1]
d2 = [2, 4]
q = []

for i in d1:
    for j in d2:
        heapq.heappush(q, [i + j, i, j])

print([heapq.heappop(q) for _ in range(len(q))])

输出结果：

[[3, 1, 2], [5, 1, 4], [5, 3, 2], [7, 3, 4], [7, 5, 2], [9, 5, 4]]


​