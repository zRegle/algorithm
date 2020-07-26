/* Leetcode 179.最大数
 * 给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。
 * 示例 1:
 *  输入: [10,2
 *  输出: 21
 * 示例 2
 *  输入: [3,30,34,5,9
 *  输出: 953433
 * 说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int size = nums.size();
        if (size == 0) return "";
        vector<string> str(size);
        bool all_zero = true;
        /* 先转化为字符串 */
        for (int idx = 0; idx < size; idx++) {
            if (nums[idx] != 0)
                all_zero = false;
            str[idx] = to_string(nums[idx]);
        }
        if (all_zero)
            /* nums数组全为0 */
            return "0";
        /* 自定义排序, 尽量保证拼接后位数高的数字越大 */    
        auto cmp = [](const string& s1, const string& s2) -> bool {
            int l1 = s1.length(), l2 = s2.length();
            /* 假设拼接后结果为str, 长度为l1 + l2
             * d1, d2分别为s1放在前面和s2放在前面, str[i]代表的数字 */
            char d1, d2;
            for (int i = 0; i < l1 + l2; i++) {
                d1 = i < l1 ? s1[i] : s2[i-l1];
                d2 = i < l2 ? s2[i] : s1[i-l2];
                if (d1 > d2)
                    return true;
                else if (d1 < d2)
                    return false;
            }
            /* 两者完全一致, 返回true或者false都行 */
            return true;
        };
        sort(str.begin(), str.end(), cmp);
        string res;
        for (string& s : str)
            res += s;
        return res;
    }
};