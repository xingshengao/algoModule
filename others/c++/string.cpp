string s;       // 初始化

s.size();       // 返回s的长度

s += x;         // 把x加到s的末尾

s.find(x);      // 查找x在s中第一次出现的位置，没有则返回-1

s.substr(pos, len);     // 从位置pos开始截取长度为len的子串

s.insert(pos, t);       // 在位置pos处插入字符串t

s.erase(pos, len);      // 从位置pos开始删除长度为len的子串
