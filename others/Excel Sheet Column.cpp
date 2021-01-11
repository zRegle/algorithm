#include <string>
#include <algorithm>
using namespace std;

/* Leetcode 168.Excel表列名称
 * 给定一个正整数, 返回它在Excel表中相对应的列名称 
 * 示例 1:
 *  输入: 1
 *  输出: "A"
 * 示例 2:
 *  输入: 28
 *  输出: "AB"
 * 示例 3:
 *  输入: 701
 *  输出: "ZY"
 */
//26进制, 满26就用'Z'表示, 超过26才进位
class Solution1 {
public:
    string convertToTitle(int n) {
        string ans;
        //从左到右分别计算个十百千...
        while (n) {
            int mod = n % 26;
            n /= 26;
            if (!mod) {
                //刚好满26
                ans += 'Z';
                //本来需要进位的, 但我们用'Z'来表示26, 没有进位
                //所以下一位就缺少了进位过来的'1', 所以需要n--
                n--;
            } else {
                ans += (char)('A'-1 + mod); //注意取模后与字母的对应关系
            }
        }
        //反转, 才是我们要的从右到左个十百千...
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/* Leetcode 171.Excel表列序号
 * 给定一个Excel表格中的列名称, 返回其相应的列序号.
 * 示例 1:
 *  输入: "A"
 *  输出: 1
 * 示例 2:
 *  输入: "AB"
 *  输出: 28
 * 示例 3:
 *  输入: "ZY"
 *  输出: 701
 */
class Solution2 {
public:
    int titleToNumber(string& s) {
        int ans = 0;
        for (char c : s)
            ans = ans * 26 + c - 'A' + 1;
        return ans;
    }
};