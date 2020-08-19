/* Leetcode 220.存在重复元素 III
 * 在整数数组nums中，是否存在两个下标i和j，
 * 使得nums[i]和nums[j]的差的绝对值小于等于t，且满足i和j的差的绝对值也小于等于ķ。
 * 如果存在则返回 true，不存在返回 false。
 */
#include <vector>
#include <set>
using namespace std;

/* 依旧是滑动窗口 */
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int size = nums.size();
        if (size < 2) return false;
        /* long是防止溢出
         * set会对元素进行排序, 这样用lower_bound效率更高
         */
        set<long> s;
        for (int i = 0; i < size; i++) {
            long val = (long)nums[i];
            /* nums[i]-t为向后查找 */
            auto it = s.lower_bound(val - t);
            if (it != s.end() && val + t >= *it)
                /* val + t >= *it确保找到的不会超过范围 */
                return true;
            s.insert(val);
            if (s.size() > k)
                s.erase(nums[i-k]);
        }
        return false;
    }
};