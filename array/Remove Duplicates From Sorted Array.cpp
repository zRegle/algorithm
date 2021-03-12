/* Leetcode 26
 * 给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
 * 不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 * 示例 1:
 * 给定数组 nums = [1,1,2], 
 * 函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。 
 * 你不需要考虑数组中超出新长度后面的元素。
 * 示例 2:
 * 给定 nums = [0,0,1,1,1,2,2,3,3,4],
 * 函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
 * 你不需要考虑数组中超出新长度后面的元素。
 */

#include <iostream>
#include <vector>
using namespace std;

//双指针法, 简单明了一看就懂
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int duplicate = 0;
        int size = nums.size();
        if (size < 2) return size;
        int prev = 0, cur = 1;
        while (cur < size) {
            //cur指针一直移动到第一个跟prev不相等的元素
            for (; cur < size && nums[prev] == nums[cur]; cur++, duplicate++);
            //将cur指向的元素复制到prev的下一个元素中
            //(注意, 之前prev下一个元素有可能跟prev相同, 这样就可以覆盖掉重复的元素了)
            if (cur < size) {
                nums[++prev] = nums[cur];
                cur++;
            }
        }
        return size - duplicate;
    }
};