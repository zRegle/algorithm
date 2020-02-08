/* Leetcode 128.最长连续序列
 * 给定一个未排序的整数数组，找出最长连续序列的长度。
 * 要求算法的时间复杂度为O(n)
 * 示例:
 *  输入: [100, 4, 200, 1, 3, 2]
 *  输出: 4
 *  解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    int longestConsecutive(vector<int>& nums) {
        //以key作为边界的最长连续序列的长度
        //例如nums = {1,2,3,4,5}, map[1] = map[5] = 5
        unordered_map<int, int> map;
        int maxLen = 0;
        for (int n : nums) {
            if (map.find(n) == map.end()) { //该数字还没出现过
                unordered_map<int, int>::iterator it;
                it = map.find(n-1);
                //n-1所在的最长序列, 因为n之前还没出现过, 所以map[n-1]实际上相当于以n结尾的最长连续序列长度
                int left = it == map.end() ? 0 : it->second;
                it = map.find(n+1);
                //n+1所在的最长序列, 因为n之前还没出现过, 所以map[n+1]实际上相当于以n开始的最长连续序列长度
                int right = it == map.end() ? 0 : it->second;
                int len = left + right + 1;
                map[n] = len;
                maxLen = max(maxLen, len);
                //更新n左右两个边界
                map[n-left] = len; map[n+right] = len;
            }
        }
        return maxLen;
    }
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set;
        for (int n : nums) set.insert(n); //先把所有元素加入到set中
        int maxLen = 0;
        for (int n : nums) {
            if (set.find(n-1) == set.end()) {
                //当前的数字是序列的起点
                int val = n, len = 1;
                //不断尝试扩展序列
                while (set.find(++val) != set.end()) len++;
                maxLen = max(len, maxLen);
            }
        }
        return maxLen;
    }
};

//时间O(nlogn), 空间O(1)的动态规划做法
//测出来速度更快一些
class Solution3 {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end()); //排序O(nlogn)
        int prevLen = 1, maxLen = 1;
        for (int i = 1; i < nums.size(); i++) { //遍历O(n)
            if (nums[i] == nums[i-1] + 1) {
                int curLen = prevLen + 1;
                maxLen = max(maxLen, curLen);
                prevLen = curLen;
            } else if (nums[i] > nums[i-1]) {
                prevLen = 1;
            }
        }
        return maxLen;
    }
};