deque<int> q    // 初始化

q.push_back(x)  // 向容器尾部添加一个元素

q.push_front(x) // 向容器头部添加一个元素

q.pop_back()    // 删除容器最后一个元素

q.pop_front()   // 删除容器第一个元素

q[1] = 100      // 可以使用下标访问数据

q.at(1) = 100   // 使用at方法

q.front()       // 返回头部引用

q.back()        // 返回尾部引用

q.size()        // 返回容器中元素个数

q.empty()       // 判断容器是否为空

q.resize(n)     // 重新制定容器的长度，默认用0填充

q.insert(pos, elem)     // 在pos位置插入一个elem元素的拷贝，返回新数据的位置

q.insert(pos, n, elem)  // 在pos位置插入n个elem元素，无返回值

q.clear()       // 清空容器的所有元素

q.erase(pos)    // 删除pos位置的数据，返回下一个数据的位置

q.erase(beg, end)   // 删除[beg, end)区间的元素，返回下一个数据的位置

for (int i = 0; i < q.size(); i++) {    // 迭代
    cout << q[i] << ' ';
}
