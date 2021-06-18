/**
 * Leetcode 768.最多能完成排序的块 II
 * 这个问题和“最多能完成排序的块”相似，
 * 但给定数组中的元素可以重复，输入数组最大长度为2000，其中的元素最大为10**8。
 * arr是一个可能包含重复元素的整数数组，我们将这个数组分割成几个“块”，
 * 并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。
 * 我们最多能将数组分成多少块？
 *
 * 示例 1:
 *  输入: arr = [5,4,3,2,1]
 *  输出: 1
 *  解释:
 *  将数组分成2块或者更多块，都无法得到所需的结果。
 *  例如，分成 [5, 4], [3, 2, 1] 的结果是 [4, 5, 1, 2, 3]，这不是有序的数组。
 * 示例 2:
 *  输入: arr = [2,1,3,4,4]
 *  输出: 4
 *  解释:
 *  我们可以把它分成两块，例如 [2, 1], [3, 4, 4]。
 *  然而，分成 [2, 1], [3], [4], [4] 可以得到最多的块数。
 *
 * 注意:
 *  (1)arr的长度在[1, 2000]之间。
 *  (2)arr[i]的大小在[0, 10**8]之间。
 */
#include <vector>
#include <stack>
using std::vector;
using std::stack;

/**
 * 滑动窗口参考sliding window文件夹
 * 贪心参考greedy文件夹
 */

/**
 * 跟769类似, 从左到右扫描, 维护一个当前最大值maxVal
 * 当curVal < maxVal时, 我们要找到curVal左边第一个大于curVal的值firstBigger
 * 最后合并成[firstBigger, curVal]的这样一个区间
 * 本质上是一个单调递减栈, 栈顶到栈底单调递减
 * 具体解析看
 * https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii/solution/zui-duo-neng-wan-cheng-pai-xu-de-kuai-ii-deng-jie-/
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        /* 单调栈, 栈顶是当前数字左边区间的最大值 */
        stack<int> stk;
        for (int x : arr) {
            /* 栈空或者当前值大于左边区间的最大值则入栈 */
            if (stk.empty() || x >= stk.top())
                stk.push(x);
            else {
                /* 保存左边区间的最大值 */
                int tmp = stk.top();
                /* 找到x左边第一个大于x的值, 合并到一个区间 */
                while (!stk.empty() && stk.top() > x)
                    stk.pop();
                /* 合并后的区间最大值仍然是tmp */
                stk.push(tmp);
            }
        }
        return stk.size();
    }
};