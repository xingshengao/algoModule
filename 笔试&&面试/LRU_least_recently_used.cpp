#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// 想象你有一摞书,
// get 把一本书抽出来, 放在最上面
// put 放入一本新书,
// 如果已经有这个key, 则把这个key抽出来放在最上面并替换value,
// 如果没有这本书, 就放在最上面,
// 如果容量超过了capacit, 把最下面的书移除
struct Node {
    int key, value;
    Node *prev, *next;
    Node() {}
    Node(int k, int v) : key(k), value(v) {}
};
// 需要一个哨兵节点,dummy,一开始dummy的prev和next都指向dummy, 随着节点的插入, dummy的next指向链表的第一个节点, prev指向链表的最后一个节点
// Node存储key是为了方便哈希表中的删除
class LRUCache {
   private:
    int capacity;
    Node* dummy;  // 哨兵节点
    unordered_map<int, Node*> key_to_node;
    // 删除一个节点, 抽出一本书
    void remove(Node* x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    // 在链表头部添加一个节点
    void push_front(Node* x) {
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }
    Node* get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) return nullptr;  // 没有这本书
        auto node = it->second;
        remove(node);      // 把这本书抽出来
        push_front(node);  // 把这本书放在最上面
        return node;
    }

   public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->dummy = new Node();
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    int get(int key) {
        auto node = get_node(key);
        if (node == nullptr) return -1;
        return node->value;
    }

    void put(int key, int value) {
        auto node = get_node(key);
        if (node != nullptr) {  // 找到了这本书
            node->value = value;
            return;
        }
        // 没找到这本书
        Node* node = new Node(key, value);
        key_to_node[key] = node;
        push_front(node);
        // 判断容量是否超出了
        if (key_to_node.size() > capacity) {
            auto back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node);
            delete back_node;
        }
    }
};