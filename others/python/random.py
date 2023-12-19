​
导入：
import random

1、random.random()：返回一个随机数，其在0至1的范围之内
>>> random.random()
0.7812830682677472

 2、random.uniform()：在指定范围内生成随机数，其有两个参数，一个是范围上限，一个是范围下线
>>> random.uniform(2, 6)
5.0808293477776

3、random.randint()：随机生成指定范围内的整数，其有两个参数，一个是范围上限，一个是范围下线
>>> random.randint(3, 5)
3

 4、random.randrange()：在指定范围内，按指定基数递增的集合中获得一个随机数，有三个参数，前两个参数代表范围上限和下限，第三个参数是递增增量
>>> random.randrange(1, 5, 2)
3

 5、random.choice()：从序列中获取一个随机元素
>>> random.choice("nreyong")
'e'

 6、random.shuffle()：将一个列表中的元素打乱，随机排序
>>> nums = [1, 2, 3]
>>> random.shuffle(nums)
>>> nums
[2, 1, 3]

 7、random.sample()：从指定序列中随机获取指定长度的片段，原有序列不会改变，有两个参数，第一个参数代表指定序列，第二个参数是需获取的片段长度
>>> nums = [1, 2, 3, 4, 5]
>>> random.sample(nums, 3)
[1, 5, 4]

 

​