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
#include <unordered_map>
using std::vector;
using std::unordered_map;
using std::sort;

/**
 * 单调栈参考monotonic stack文件夹
 * 贪心参考greedy文件夹
 */

/**
 * 滑动窗口, 将原数组排序, 设为sorted
 * arr进行分块后, 每一个分块和sorted中对应的分块数字是一样的, 只是顺序不同
 * 既然每个分块中数字是一样的, 那它们的和也是一样的
 * 我们可以用一个滑动窗口同时扫描arr和sorted, 当窗口中数字的和一样时, 就将arr进行分块
 *
 * 注意, 不可能出现"arr中的某个chunk之和跟sorted一样, 但arr不是sorted的permutation"
 * 用数学归纳 + 反证法证明:
 * 假设arr的某个chunk: {arr[i], ..., arr[j]}
 * 对应sorted的chunk: {sorted[i], ..., sorted[j]}
 * 存在arr[i]排序后位置 ∉ [i, j]
 *
 * 将arr和sorted以这个chunk为基准, 划分成三部分
 * {arr[0], ..., arr[i-1]}, {arr[i], ..., arr[j]}, {arr[j+1], ..., arr[n]}
 * {sorted[0], ..., sorted[i-1]}, {sorted[i], ..., sorted[j]}, {sorted[j+1], ..., sorted[n]}
 *
 * 易知至少还有i' ∈ [i, j], 有arr[i‘]排序后位置 ∉ [i, j]
 * 且arr[i] ≠ arr[i'], 假设arr[i'] < arr[i]
 * 有arr[i'] < [sorted[i], sorted[j]] < arr[i]
 * (当存在一个数字不对应, 则至少存在两个不一样, 且一大一小)
 *
 * 易知Sum(sorted, [0,i-1]) <= Sum(sorted, [i,j]) <= Sum(sorted, [j+1, n])
 *    Sum(sorted, [0,n]) == Sum(arr, [0, n])
 * 由数学归纳可知, {arr[0], ..., arr[i-1]}是{sorted[0], ..., sorted[i-1]}的permutation
 * 因此有结论:
 *    (1)Sum(sorted, [j+1, n]) == Sum(arr, [j+1, n])
 *    (2)arr[i'], arr[i]排序后的位置在[j+1, n]
 *
 * 又因为sorted[n] >= sorted[j+1] >= sorted[j] > arr[i']
 * 所以无论如何结论(1)和(2)都是矛盾的
 */
class Solution0 {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        int ans = 0;
        unsigned long sum1 = 0, sum2 = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum1 += arr[i];
            sum2 += sorted[i];
            if (sum1 == sum2) ans++;
        }
        return ans;
    }
};

/**
 * 更直观的滑动窗口
 * 我们知道数组 arr 在排序之后一定跟整个数组排序后相应的地方完全相同，即 expect = sorted(arr)。
 * 如果前 k 个元素的个数减去排序后前 k 个元素的个数都为 0 的话，
 * 那这前 k 个元素是可以成为一个合法的分块的。对于整个数组可以重复这一过程。
 * 用变量 nonzero 来计数目前差值不等于 0 的字符的个数。
 */
class Solution1 {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> expect = arr;
        sort(expect.begin(), expect.end());
        unordered_map<int, int> diff;
        int nonzero = 0, ans = 0;
        for (int i = 0; i < arr.size(); i++) {
            int x = arr[i], y = expect[i];

            if (diff.find(x) == diff.end())
                diff[x] = 1;
            else
                diff[x]++;
            if (diff[x] == 0) nonzero--;
            /* 注意: 我们只关心差值不为0的有多少种数字
             * 而不在乎这个数字差了多少个 */
            if (diff[x] == 1) nonzero++;

            if (diff.find(y) == diff.end())
                diff[y] = -1;
            else
                diff[y]--;
            if (diff[y] == 0) nonzero--;
            /* 注意: 我们只关心差值不为0的有多少种数字
             * 而不在乎这个数字差了多少个 */
            if (diff[y] == -1) nonzero++;

            if (nonzero == 0) ans++;
        }
        return ans;
    }
};