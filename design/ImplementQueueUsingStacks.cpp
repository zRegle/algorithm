/* Leetcode 232.用栈实现队列 */
#include <stack>
using namespace std;

/* 入队时间复杂度O(1)
 * 出队时间复杂度最坏O(n), 摊还复杂度O(1)
 * 对于摊还复杂度, 因为无论是哪个元素,
 * 都是入栈两次(进一次A和一次B), 出栈两次(同理),
 * 所以平均复杂度都是O(1)
 */
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if (s1.empty())
            front = x;
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int x = s2.top(); s2.pop();
        return x;
    }
    
    /** Get the front element. */
    int peek() {
        if (!s2.empty())
            return s2.top();
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty() && s2.empty();
    }

private:
    stack<int> s1, s2;
    int front;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */