/**
 * Leetcode 739. 每日温度
 * 请根据每日 气温 列表，重新生成一个列表。
 * 对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。
 * 如果气温在这之后都不会升高，请在该位置用 0 来代替。
 *
 * 例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，
 * 你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。
 *
 * 提示：气温 列表长度的范围是 [1, 30000]。
 * 每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
 */
#include <vector>
#include <stack>
using namespace std;

/* 单调栈即可解决 */

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> stk;
        /* 单调递增栈, 从栈顶到栈底单调递增 */
        int n = T.size();
        auto ans = vector<int>(n, 0);
        for (int i = 0; i < n; i++) {
            /* 温度比栈顶的温度要低就入栈 */
            if (stk.empty() || T[stk.top()] >= T[i]) {
                stk.push(i);
            } else {
                /* 栈顶遇到比它温度高的 */
                while (!stk.empty() && T[stk.top()] < T[i]) {
                    int idx = stk.top();
                    stk.pop();
                    ans[idx] = i - idx;
                }
                stk.push(i);
            }
        }
        return ans;
    }
};