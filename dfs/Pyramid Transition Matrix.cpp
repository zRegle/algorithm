/**
 * Leetcode 756. 金字塔转换矩阵
 * 现在，我们用一些方块来堆砌一个金字塔。 每个方块用仅包含一个字母的字符串表示。
 *
 * 使用三元组表示金字塔的堆砌规则如下：
 *  对于三元组(A, B, C) ，“C”为顶层方块，方块“A”、“B”分别作为方块“C”下一层的的左、右子块。
 *  当且仅当(A, B, C)是被允许的三元组，我们才可以将其堆砌上。
 *
 * 初始时，给定金字塔的基层 bottom，用一个字符串表示。一个允许的三元组列表 allowed，
 * 每个三元组用一个长度为 3 的字符串表示。
 * 如果可以由基层一直堆到塔尖就返回 true ，否则返回 false 。
 *
 * 示例 1：
 *  输入：bottom = "BCD", allowed = ["BCG", "CDE", "GEA", "FFF"]
 *  输出：true
 *  解析：可以堆砌成这样的金字塔:
 *       A
 *      / \
 *     G   E
 *    / \ / \
 *   B   C   D
 *   因为符合('B', 'C', 'G'), ('C', 'D', 'E') 和 ('G', 'E', 'A') 三种规则。
 *
 * 示例 2：
 *  输入：bottom = "AABA", allowed = ["AAA", "AAB", "ABA", "ABB", "BAC"]
 *  输出：false
 *  解析：无法一直堆到塔尖。
 *    注意, 允许存在像 (A, B, C) 和 (A, B, D) 这样的三元组，其中 C != D。
 *
 * 提示：
 *  (1)bottom 的长度范围在 [2, 8]。
 *  (2)allowed 的长度范围在[0, 200]。
 *  (3)方块的标记字母范围为{'A', 'B', 'C', 'D', 'E', 'F', 'G'}。
 */
#include <string>
#include <vector>
using std::string;
using std::vector;

/* 字母范围 */
#define COUNT 7
class Solution {
public:
    bool pyramidTransition(string& bottom, vector<string>& allowed) {
        map.resize(COUNT, vector<int>(COUNT, 0));
        for (const string& triple : allowed) {
            int x = triple[0] - 'A';
            int y = triple[1] - 'A';
            int z = triple[2] - 'A';
            map[x][y] |= 1 << z;
        }
        string next;
        return solve(bottom, next);
    }

private:
    /* 状态压缩
     * 我们将字母编号, 即A -> 0, B -> 1, C -> 2 ... G -> 6
     * 例如对于三元组["BCD", "BCG"]
     * map['B']['C'] = map[1][2]
     * 我们知道base为"BC"时, top可以是‘D’或者'G'. 我们记map[1][2] = x
     * 那么x中'D'和'G'对应的bit应该为1, 因此x = 0b1001000
     */
    vector<vector<int>> map;
    /**
     * 判断当前bottom能否推到塔尖
     * @param bottom 当前bottom
     * @param next bottom的上一层, 即下一轮的bottom
     * @return true or false
     */
    bool solve(string& bottom, string& next) {
        if (bottom.length() == 1)
            /* 达到塔尖, 返回true */
            return true;
        int len = next.length();
        if (len == bottom.length()-1) {
            /* 新的bottom构建完, 递归上一层 */
            string _next;
            return solve(next, _next);
        }
        /* next.length = bottom.length - 1
         * 因此next[i]的base就是bottom[i]和bottom[i+1]
         */
        int x = bottom[len] - 'A';
        int y = bottom[len+1] - 'A';
        for (int i = 0; i < COUNT; i++) {
            if (map[x][y] & (1 << i)) {
                /* 对于当前x和y组成的base来说, 这个top合法 */
                next += (char)('A' + i);
                if (solve(bottom, next))
                    return true;
                next.pop_back(); /* 回溯 */
            }
        }
        return false;
    }
};