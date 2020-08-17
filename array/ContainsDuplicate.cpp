/* 217. 存在重复元素
 * 给定一个整数数组，判断是否存在重复元素。
 * 如果任意一值在数组中出现至少两次，函数返回true 。如果数组中每个元素都不相同，则返回false 。
 */
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

/* Easy题不愧是Easy题 */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> set;
        for (int n : nums) {
            if (set.find(n) != set.end())
                return true;
            set.insert(n);
        }
        return false;
    }
};

class Solution1 {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1])
                return true;
        }
        return false;
    }
};