/* Leetcode 167.两数之和2--输入有序数组
 * 给定一个已按照升序排列的有序数组，找到两个数使得它们相加之和等于目标数。
 * 函数应该返回这两个下标值index1和index2，其中index1必须小于index2。
 * 说明:
 *  返回的下标值（index1 和 index2）不是从零开始的。
 *  你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
 */
#include <vector>
using namespace std;

//双指针法
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int len = numbers.size();
        if (len < 2) return ans;
        int left = 0, right = len-1;
        while (left < right) {
            int first = numbers[left], second = numbers[right];
            if (first + second == target) {
                ans.push_back(left + 1);
                ans.push_back(right + 1);
                return ans;
            } else if (first + second > target) {
                right--;
            } else {
                left++;
            }
        }
        return ans;
    }
};