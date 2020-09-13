#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int calculate(string expr) {
        int n = expr.size();
        stack<int> s;
        int num = 0, pre;
        /* 启动操作符, 保证第一个数字顺利入栈
         * 因为题目确保只有非负整数, 所以可以设置成'+'
         */
        char op = '+';
        for (int i = 0; i < n; i++) {
            char c = expr[i];
            if (isdigit(c)) {
                num *= 10;
                num += expr[i] - '0';
            }
            /* (1)!isdigit -> 只有在当前字符不是数字下才进入条件分支
             * (2)c != ' ' -> 跳过空格
             * (3)i == n-1 -> 处理最后一个数字, 跟栈顶元素计算
             * (1)在处理最后一个数字时会为false, 但是(3)是true, 依然会处理最后一个数字
             */
            if (!isdigit(c) && c != ' ' || i == n-1) {
                /* 检查上一个运算符是啥 */
                switch (op) {
                    case '+':
                        s.push(num);
                        break;
                    case '-':
                        s.push(-num);
                        break;
                    case '*':
                        pre = s.top(); s.pop();
                        s.push(pre * num);
                        break;
                    case '/':
                        pre = s.top(); s.pop();
                        s.push(pre / num);
                        break;
                    default:
                        break;
                }
                /* 更新运算符, 用于下一次运算 */
                op = c;
                num = 0;
            }
        }
        int res = 0;
        while (!s.empty()) {
            res += s.top();
            s.pop();
        }
        return res;
    }
};