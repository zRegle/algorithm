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
#include <algorithm>
using std::vector;
using std::max;
using std::min;

/**
 * 单调栈参考monotonic stack文件夹
 * 滑动窗口参考sliding window文件夹
 */

/**
 * 贪心:
 * 只有对于某个位置，其左边（包括本身）的最大值不大于其右侧（不包括本身）的最小值，在该处就可以分段
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> lmax(n, INT_MIN);
        vector<int> rmin(n, INT_MAX);
        lmax[0] = arr[0];
        rmin[n-1] = arr[n-1];
        for (int i = 1; i < n; i++) {
            lmax[i] = max(lmax[i-1], arr[i]);
            rmin[n-i-1] = min(rmin[n-i], arr[n-i-1]);
        }
        int ans = 1;
        for (int i = 0; i < n-1; i++) {
            ans += lmax[i] <= rmin[i+1];
        }
        return ans;
    }
};