/* Leetcode 150.逆波兰表达式求值
 * 根据逆波兰表示法(即四则运算的后缀表达式),求表达式的值.
 * 示例 1：
 *  输入: ["2", "1", "+", "3", "*"]
 *  输出: 9
 *  解释: ((2 + 1) * 3) = 9
 * 示例 2：
 *  输入: ["4", "13", "5", "/", "+"]
 *  输出: 6
 *  解释: (4 + (13 / 5)) = 6
 */
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//遇到数字就入栈, 遇到运算符就pop出两个数, 计算, 再将结果入栈
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if (tokens.empty()) return 0;
        stack<int> s;
        for (const string& t : tokens) {
            int len = t.length();
            if (isdigit(t[0]) || len > 1) {
                s.push(stoi(t));
            } else {
                int op2 = s.top(); s.pop();
                int op1= s.top(); s.pop();
                int res = 0;
                if (t == "+") {
                    res = op1 + op2;
                } else if (t == "-") {
                    res = op1 - op2;
                } else if (t == "*") {
                    res = op1 * op2;
                } else if (t == "/") {
                    res = op1 / op2;
                }
                s.push(res);
            }
        }
        return s.top();
    }
};