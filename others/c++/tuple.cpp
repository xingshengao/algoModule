#include <bits/stdc++.h>

using namespace std;

int main() {
    tuple<string, int, int> t("nreyog", 22, 66);    // 初始化

    cout << get<0> (t) << endl;     // 输出第0个元素的值
    
    get<2> (t) = 111;   // 修改第2个元素的值，因为返回的是引用，所以可以直接赋值
    cout << get<2> (t) << endl;
    
    cout << tuple_size<decltype(t)>::value << endl; // 输出元组t的元素个数
   
}
