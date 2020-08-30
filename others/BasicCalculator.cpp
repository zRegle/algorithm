/* Leetcode 224.基本计算器
 * 实现一个基本的计算器来计算一个简单的字符串表达式的值。
 * 字符串表达式可以包含左括号( ，右括号) ，加号+ ，减号- ，非负整数和空格  。
 * 可以假设所给定的表达式都是有效的。
 */
#include <string>
#include <stack>
#include <list>
using namespace std;

/* 中缀转后缀计算 */
class Solution {
public:
    int calculate(string& s) {
        list<string> suffix = infix2suffix(s);
        stack<int> stk;
        for (string& token : suffix) {
            if (token == "+") {
                int op1 = stk.top(); stk.pop();
                int op2 = stk.top(); stk.pop();
                stk.push(op1 + op2);
            } else if (token == "-") {
                int op2 = stk.top(); stk.pop();
                int op1 = stk.top(); stk.pop();
                stk.push(op1 - op2);
            } else {
                int number = stoi(token);
                stk.push(number);
            }
        }
        return stk.top();
    }
private:
    /* 中缀转后缀 */
    list<string> infix2suffix(string& s) {
        int idx = 0;
        stack<string> _operator; /* 操作符栈 */
        list<string> suffix; /* 后缀表达式 */
        while (idx < s.length()) {
            if (s[idx] == ' ') {
                idx++;
                continue;
            }
            if (s[idx] == '(') {
                _operator.push("(");
            } else if (s[idx] == ')') {
                /* 遇到右括号, 将栈里元素一直出栈输出到后缀表达式
                 * 直到遇到左括号(左括号不入栈)
                 */
                while (_operator.top() != "(") {
                    suffix.push_back(_operator.top());
                    _operator.pop();
                }
                _operator.pop();
            } else if (s[idx] == '+' || s[idx] == '-') {
                if (!_operator.empty()) {
                    /* 栈不为空, 检查栈顶元素的优先级是否大于当前元素
                     * 如果是则入栈, 如果不是则pop栈顶元素, 继续比较
                     */
                    while (!_operator.empty() &&
                           (_operator.top() == "+" || _operator.top() == "-")) {
                        suffix.push_back(_operator.top());
                        _operator.pop();
                    }
                }
                /* 操作符入栈 */
                string op(1, s[idx]);
                _operator.push(op);
            } else {
                /* 数字直接输出到后缀表达式 */
                string number;
                while ('0' <= s[idx] && s[idx] <= '9') {
                    number += s[idx];
                    idx++;
                }
                suffix.push_back(number);
                idx--;
            }
            idx++;
        }
        /* 操作符栈剩余元素全部pop到后缀表达式 */
        while (!_operator.empty()) {
            suffix.push_back(_operator.top());
            _operator.pop();
        }
        return suffix;
    }
};

/* 比较tricky的一种方法 */
class Solution1 {
public:
    int calculate(string& expr) {
        stack<int> s; /* 临时结果栈 */
        /* res: 当前表达式的运算结果
         * sign: 符号flag
         */
        int res = 0, n = expr.size(), sign = 1;
        for (int i = 0; i < n; i++) {
            int num = 0;
            if (expr[i] >= '0') {
                /* 数字 */
                while (i < n && expr[i] >= '0') {
                    num *= 10;
                    num += expr[i] - '0';
                    i++;
                }
                i--;
                /* 更新当前运算结果 */
                res += sign * num;
            }
            else if (expr[i] == '+') sign = 1;
            else if (expr[i] == '-') sign = -1;
            else if (expr[i] == '(') {
                /* 左括号, 需要计算括号里的值
                 * 保存当前运算结果和符号位
                 * res, sign复原, 用于计算括号里的值
                 */
                s.push(res);
                s.push(sign);
                res = 0, sign = 1;
            } else if (expr[i] == ')') {
                /* 右括号, 一对括号里的值已经计算完毕, 保存到res里
                 * res首先乘上符号位, 然后与之前的运算结果相加
                 */
                res *= s.top(); s.pop();
                res += s.top(); s.pop();
            }
        }
        return res;
    }
};