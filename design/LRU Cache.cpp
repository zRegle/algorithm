/* Leetcode 146.LRU缓存机制
 * 设计和实现一个LRU(最近最少使用)缓存机制.它应该支持以下操作:获取数据get和写入数据put.
 * 获取数据 get(key):
 *  如果密钥(key)存在于缓存中，则获取密钥的值(总是正数), 否则返回-1.
 * 写入数据put(key, value):
 *  如果密钥不存在,则写入其数据值.当缓存容量达到上限时,它应该在写入新数据之前删除最近最少使用的数据值,
 *  从而为新的数据值留出空间.
 * 要求: O(1)时间复杂度内完成这两种操作
 */
#include <unordered_map>
using namespace std;

//双向链表节点
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int key, int value) {
        this->key = key;
        this->value = value;
        prev = next = nullptr;
    }
};

//设计思路:
//1.将cache按照使用次序连接成双向链表, 需要删除数据时就删除头结点
//2.将key和cache放到哈希表中
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        curSize = 0;
        head = tail = nullptr;
    }

    int get(int key) {
        auto it = map.find(key);
        if (it != map.end()) {
            auto node = it->second;
            del(node); add(node); //每次使用时就将cache移到链表尾
            return node->value;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            auto node = it->second;
            del(node); add(node); //每次使用时就将cache移到链表尾
            node->value = value;
        } else {
            auto node = new Node(key, value);
            add(node); //加到链表尾部
            map[key] = node; //插入键值对
            if (curSize == capacity) {
                int delKey = head->key;
                map.erase(delKey); //删除键值对
                auto target = head;
                del(target); //删除表头
                delete target; //释放内存
            } else {
                curSize++;
            }
        }
    }
private:
    int capacity;
    int curSize;
    unordered_map<int, Node*> map;
    Node* head, *tail;

    void del(Node* node) {
        if (!node) return;
        if (head == tail && node == head) {
            head = tail = nullptr;
        } else if (node == head){
            auto new_head = head->next;
            head = new_head;
            new_head->prev = nullptr;
        } else if (node == tail) {
            auto new_tail = tail->prev;
            tail = new_tail;
            new_tail->next = nullptr;
        } else {
            auto next = node->next;
            auto prev = node->prev;
            prev->next = next;
            next->prev = prev;
        }
        node->next = nullptr;
        node->prev = nullptr;
    }

    void add(Node* node) {
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
};