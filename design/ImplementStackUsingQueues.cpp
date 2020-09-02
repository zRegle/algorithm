/* Leetcode 225.用队列实现栈
 * 两个队列模拟栈
 */
#include <queue>
using namespace std;

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        p1 = &q1;
        p2 = &q2;
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        p1->push(x);
        top_item = x;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int size = p1->size();
        /* 将p1指向的队列的所有元素pop到p2的队列里, 只留最后一个元素
         * 同时更新top_item
         */
        for (int i = 0; i < size-1; i++) {
            p2->push(p1->front());
            top_item = p1->front();
            p1->pop();
        }
        int item = p1->front();
        p1->pop();
        /* 此时p1指向的队列已经没有元素了, p2指向的有元素
         * 交换p1和p2, 方便之后的操作
         */
        swap(p1, p2);
        return item;
    }
    
    /** Get the top element. */
    int top() {
        return top_item;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return p1->empty() && p2->empty();
    }

private:
    queue<int> q1, q2;
    /* 指针是方便交换 */
    queue<int>* p1, *p2;
    /* 栈顶元素 */
    int top_item;
};