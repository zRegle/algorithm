/**
 * Leetcode 946. 验证栈序列
 * 给定 pushed 和 popped 两个序列，每个序列中的值都不重复，
 * 只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；
 * 否则，返回 false 。
 *
 * 示例 1：
 *  输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
 *  输出：true
 *  解释：我们可以按以下顺序执行：
 *   push(1), push(2), push(3), push(4), pop() -> 4,
 *   push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
 * 示例 2：
 *  输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
 *  输出：false
 *  解释：1 不能在 2 之前弹出。
 *
 * 提示：
 *  (1)0 <= pushed.length == popped.length <= 1000
 *  (2)0 <= pushed[i], popped[i] < 1000
 *  (3)pushed 是 popped 的排列。
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.empty() && popped.empty()) return true;
        if (pushed.empty() || popped.empty()) return false;
        stack<int> stk;
        for (int i = 0, j = 0; i < pushed.size(); i++) {
            stk.push(pushed[i]);
            /* 弹出序列是栈顶元素时, 就一直出栈 */
            while (j < pushed.size() && !stk.empty() &&
                    stk.top() == popped[j]) {
                stk.pop();
                j++;
            }
        }
        /* 弹出序列要求的值为x, 栈顶却为y,
         * 并且压栈序列已经遍历完了, 后续没有x值供压入
         * 此时栈不为空, 不满足要求 */
        return stk.empty();
    }
};