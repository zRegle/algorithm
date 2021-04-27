/**
 * Leecode 565.数组嵌套
 * 索引从0开始长度为N的数组A，包含0到N - 1的所有整数。找到最大的集合S并返回其大小，
 *
 * 其中 S[i] = {A[i], A[A[i]], A[A[A[i]]], ... }且遵守以下的规则:
 * 假设选择索引为i的元素A[i]为S的第一个元素，S的下一个元素应该是A[A[i]]，之后是A[A[A[i]]]...
 * 以此类推，不断添加直到S出现重复的元素。
 *
 * 示例 1:
 *  输入: A = [5,4,0,3,1,6,2]
 *  输出: 4
 *  解释: A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.
 *   其中一种最长的 S[K]:
 *   S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
 *
 * 提示：
 * 1.N是[1, 20,000]之间的整数。
 * 2.A中不含有重复的元素。
 * 3.A中的元素大小在[0, N-1]之间。
 */
#include <vector>
using namespace std;


/**
 * 注意题目条件: 
 * (1)A中不含有重复的元素, 因此不会出现两个集合S和S'有交集的这种情况
 * (2)A中的元素大小在[0, N-1]之间, 因此可以使A[i] += N表示A[i]已经访问过
 * 
 * 思路:
 * 遍历数组A, 从当前下标出发, 一直添加元素直到有重复元素出现
 * 中途标记已经访问过的元素
 */
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0, len = nums.size();
        for (int i = 0; i < len; i++) {
            if (nums[i] > len) continue;
            int cur = i, cnt = 0;
            while (nums[cur] < len) {
                /* 标记nums[cur]已经访问过 */
                nums[cur] = nums[cur] + len;
                /* 取模, 前往下一个元素 */
                cur = nums[cur] % len;
                cnt++;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};