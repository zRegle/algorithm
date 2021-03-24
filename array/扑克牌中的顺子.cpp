/**
 * 剑指 Offer 扑克牌中的顺子
 * 从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
 * 2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。
 * A 不能视为 14。
 *
 * 示例 1:
 *  输入: [1,2,3,4,5]
 *  输出: True
 *
 * 示例 2:
 *  输入: [0,0,1,2,5]
 *  输出: True
 *  解释：可以把两张大王看成3和4
 *
 * 限制：
 * 数组长度为 5
 * 数组的数取值为 [0, 13] .
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool isStraight(vector<int>& nums) {
        vector<int> set(14, 0);
        int maxVal = -1, minVal = 14;
        for (int x : nums) {
            /* 大王可以变成任何数字, 因此直接忽略 */
            if (x == 0) continue;
            /* 这张牌之前出现过, 肯不是顺子 */
            if (set[x] != 0) return false;
            set[x] = 1;
            maxVal = max(maxVal, x);
            minVal = min(minVal, x);
        }
        return maxVal - minVal < 5;
    }
};