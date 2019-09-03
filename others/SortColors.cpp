/* Leetcode 75
 * 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 * 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 * 注意:
 * 不能使用代码库中的排序函数来解决这道题。
 * 示例:
 * 输入: [2,0,2,1,1,0]
 * 输出: [0,0,1,1,2,2]
 */
#include <vector>
using namespace std;

//遍历两遍，第一遍确定各个颜色的个数，第二遍重写数组
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int size = nums.size();
        vector<int> c(3, 0);
        for (int color : nums)
            c[color]++;
        int idx = 0;
        for (int i = 0; i < c[0] && idx < size; idx++, i++)
            nums[idx] = 0;
        for (int i = 0; i < c[1] && idx < size; idx++, i++)
            nums[idx] = 1;
        for (int i = 0; i < c[2] && idx < size; idx++, i++)
            nums[idx] = 2;
    }
};

//1-pass, 基本思路是将0放到左边, 2换到右边, 这样1就留在中间了
class Solution2 {
    void sortColors(vector<int>& nums) {
        //p0代表0的最右边界, p2代表2的最左边界
        int p0 = 0, p2 = nums.size()-1, cur = 0;
        while (cur <= p2) {
            if (nums[cur] == 0)
                //当前是0, cur与p0交换, cur右移, 更新p0边界
                swap(nums[cur++], nums[p0++]);
            else if (nums[cur] == 2)
                //当前是2, cur与p2交换, 更新p2边界
                //此时我们不知道从p2那交换过来的元素是啥, 所以不用右移cur
                swap(nums[cur], nums[p2--]);
            else
                cur++;
        }
    }
};