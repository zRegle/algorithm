/**
 * Leetcode 769.最多能完成排序的块
 * 数组arr是[0, 1, ..., arr.length - 1]的一种排列，我们将这个数组分割成几个“块”，
 * 并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。
 * 我们最多能将数组分成多少块？
 *
 * 示例 1:
 *  输入: arr = [4,3,2,1,0]
 *  输出: 1
 *  解释:
 *  将数组分成2块或者更多块，都无法得到所需的结果。
 *  例如，分成 [4, 3], [2, 1, 0] 的结果是 [3, 4, 0, 1, 2]，这不是有序的数组。
 * 示例 2:
 *  输入: arr = [1,0,2,3,4]
 *  输出: 4
 *  解释:
 *  我们可以把它分成两块，例如 [1, 0], [2, 3, 4]。
 *  然而，分成 [1, 0], [2], [3], [4] 可以得到最多的块数。
 *
 * 注意:
 *  (1)arr 的长度在 [1, 10] 之间。
 *  (2)arr[i]是 [0, 1, ..., arr.length - 1]的一种排列
 *     即0 <= arr[i] <= arr.length-1
 */
#include <vector>
using std::vector;
using std::max;

/**
 * 注意到0 <= arr[i] <= arr.length-1
 * 要尽可能地多切块, 就要保证尽可能多的数字跟它的idx对应
 * 即arr[i] == i
 * 
 * 从左到右扫描, 维护当前最大值maxVal
 * 当maxVal == i, 代表可以进行切块
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        int ans = 0, maxVal = 0;
        for (int i = 0; i < n; i++) {
            maxVal = max(maxVal, arr[i]);
            if (maxVal == i) ans++;
        }
        return ans;
    }
};