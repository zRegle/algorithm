/* Leetcode 264.丑数 II
 * 编写一个程序，找出第 n 个丑数。
 * 丑数就是质因数只包含 2, 3, 5 的正整数。
 * 示例:
 *  输入: n = 10
 *  输出: 12
 *  解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
 *
 */
#include <vector>
#include <set>
using namespace std;

/* 动态规划方法查看dp文件夹 */

/* 丑数只能是丑数 x 丑数得到 */

/* 优先级队列, 每次取出队列头, 然后x2, x3, x5放回队列 */
class Solution {
public:
    int nthUglyNumber(int n) {
        set<unsigned long> s;
        int prime[] = {2,3,5};
        s.insert(1);
        unsigned long cnt = 1, num;
        while (num = *s.begin(), cnt < n) {
            s.erase(s.begin());
            for (int x : prime)
                s.insert(x);
            cnt++;
        }
        return (int)num;
    }
};