bitset<10000> b     // 初始化，

b.count()           // 返回true的数量

b.size()            // 返回bitset的长度

b.any()             // 若存在某一位是true，则返回true，否则返回false

b.none()            // 若所有位都是false，则返回true，否则返回false

b.set()             // 将整个bitset设置成true

b.set(pos, val = true)  // 将某一位设置成true/false

b.reset()           // 将整个bitset设置成false

b.reset(pos)        // 将某一位设置成false

b.flip()            // 翻转每一位

b.flip(pos)         // 翻转某一位
