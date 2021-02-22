/**
 * Leetcode 283. 移动零
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 示例:
 *  输入: [0,1,0,3,12]
 *  输出: [1,3,12,0,0]
 * 说明:
 *  (1)必须在原数组上操作，不能拷贝额外的数组。
 *  (2)尽量减少操作次数。
 */
#include <vector>
using std::vector;

/**
 * 空间复杂度O(N)做法:
 *
 *  void moveZeroes(vector<int>& nums) {
 *      int len = nums.size();
 *      auto ans = vector<int>(len, 0);
 *      int i = 0, idx = 0;
 *      for (int i = 0; i < len; i++) {
 *          if (nums[i] != 0)
 *              nums[idx++] = nums[i];
 *      }
 *  }
 *
 * 我们只需要模拟这个过程即可做到空间O(1)
 * 
 * 我们设两个指针left和right, 满足下面性质:
 *  (1) [0, left]为已经处理好的序列, 全不为0
 *  (2) (left, right]全为0
 * right就相当于指向原数组的指针, left就相当于指向辅助数组的指针
 */

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0, len = nums.size();
        for (int right = 0; right < len; right++) {
            if (nums[right] != 0) {
                if (right != left) {
                    nums[left] = nums[right];
                    nums[right] = 0;
                }
                left++;
            }
        }
    }
};