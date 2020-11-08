/* Leetcode 241.为运算表达式设计优先级
 * 给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。
 * 你需要给出所有可能的组合的结果。有效的运算符号包含 +, - 以及 * 。
 * 示例:
 *  输入: "2*3-4*5"
 *  输出: [-34, -14, -10, -10, 10]
 *  解释:
 *   (2*(3-(4*5))) = -34
 *   ((2*3)-(4*5)) = -14
 *   ((2*(3-4))*5) = -10
 *   (2*((3-4)*5)) = -10
 */
#include <string>
#include <vector>
using namespace std;

/* 递归分治
 * 遇到运算符, 分别计算两侧表达式不同优先级下的结果集
 * 然后再对两个结果集整合作为本次分治的结果
 */
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> ans;
        int num = 0;
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                /* 分别计算两侧表达式不同优先级下的结果集 */
                auto left = diffWaysToCompute(input.substr(0, i));
                auto right = diffWaysToCompute(input.substr(i+1, string::npos));
                /* 对两个结果集中的各个元素进行运算 */
                for (int x : left) {
                    for (int y : right) {
                        if (input[i] == '+')
                            ans.push_back(x + y);
                        else if (input[i] == '-')
                            ans.push_back(x - y);
                        else if (input[i] == '*')
                            ans.push_back(x * y);
                    }
                }
            } else {
                /* input为一个数字, 不需要进行运算, 直接字符串转数字 */
                num *= 10;
                num += input[i] - '0';
            }
        }
        if (ans.empty())
            /* base case: 表达式只有数字 */
            ans.push_back(num);
        return ans;
    }
};