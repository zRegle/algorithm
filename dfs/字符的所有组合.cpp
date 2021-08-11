/**
 * 剑指offer - 字符的所有组合
 * 输入n个字符, 求这n个字符的所有组合方案数
 * 
 * 示例:
 *  输入: a, b, c
 *  输出: 7
 *  解释: a, b, c, ab, ac, bc, abc
 *  注意: 字符相同但顺序不同, 例如"ab"和"ba", 也视作同一个组合,
 */
#include <string>
#include <vector>
using namespace std;

/* dp方法查看dp文件夹 */

class Solution {
public:
    int combination(vector<char>& chs) {
        int n = chs.size();
        for (int i = 1; i <= n; i++) {
            dfs(0, i, chs);
        }
        return cnt;
    }

private:
    int cnt = 0;
    /**
     * 求从[cur, n]这个区间选取m个字符的方案数
     * @param cur 区间左边界
     * @param m 选取多少个字符
     * @param chs 字符列表
     */
    void dfs(int cur, int m, vector<char>& chs) {
        if (m == 0) {
            /* 选够字符了, 返回 */
            cnt++;
            return;
        }
        /* 没有更多的字符可供选择, 返回 */
        if (cur == chs.size()) return;
        /* 选取当前字符 */
        dfs(cur + 1, m - 1, chs);
        /* 不选取当前字符 */
        dfs(cur + 1, m, chs);
    }
};