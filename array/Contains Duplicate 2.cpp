/* Leetcode 219.存在重复元素II
 * 给定一个整数数组和一个整数k，判断数组中是否存在两个不同的索引i和j，
 * 使得 nums[i] = nums[j]，并且i和j的差的绝对值至多为k。
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int size = nums.size();
        if (size < 2) return false;
        /* 数字 -> 下标的映射 */
        unordered_map<int, int> map;
        for (int i = 0; i < size; i++) {
            auto it = map.find(nums[i]);
            if (it == map.end()) {
                map[nums[i]] = i;
            } else {
                /* 有duplicate */
                int gap = abs(it->second - i);
                if (gap <= k)
                    return true;
                /* 它们之间的gap大于k, 更新value为i
                 * 方便下一次检测
                 */
                it->second = i;
            }
        }
        return false;
    }
};

class Solution1 {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int size = nums.size();
        if (size < 2) return false;
        unordered_set<int> set;
        for (int i = 0; i < size; i++) {
            if (set.find(nums[i]) == set.end()) {
                set.insert(nums[i]);
                if (set.size() > k)
                    /* 集合元素超过k个就删除集合中最旧的元素 */
                    set.erase(nums[i-k]);
            }
            else
                return true;
        }
        return false;
    }
};