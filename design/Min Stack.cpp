/* Leetcode 155.最小栈
 * 设计一个支持push, pop, top操作, 并能在常数时间内检索到最小元素的栈.
 */
#include <stack>
using namespace std;

class MinStack {
public:
    stack<int> data;
    stack<int> auxiliary; //辅助栈, 栈顶元素是次小值
    int val; //最小值

    MinStack() {}

    void push(int x) {
        if (data.empty()) {
            val = x; //第一个元素, 直接入栈
        } else {
            if (val >= x) {
                //x <= 当前最小值
                val = x; //更新最小值
                auxiliary.push(val); //保存次小值在辅助栈中
            }
        }
        data.push(x);
    }

    void pop() {
        int top = data.top();
        data.pop();
        if (top == val && !auxiliary.empty()) {
            //如果弹出的是最小值, 那么辅助栈的栈顶的次小值就变成了最小值
            val = auxiliary.top();
            auxiliary.pop(); //更新次小值
        }
    }

    int top() {
       return data.top();
    }

    int getMin() {
        return val;
    }
};