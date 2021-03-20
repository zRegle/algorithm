#include <vector>
using namespace std;

/* dp[i]: 第i个丑数
 * 实际上就相当于有3个丑数组, 分别是从1开始乘以2,3,5得到的序列
 * 2: 1*2, 2*2, 3*2, 4*2...
 * 3: 1*3, 2*3, 3*3, 4*3...
 * 5: 1*5, 2*5, 3*5, 4*5...
 * 然后对这个3个数组合并排序
 */
class Solution {
public:
    int nthUglyNumber(int n) {
        auto dp = vector<int>(n);
        dp[0] = 1;
        //a, b, c分别指向上述的3个数组
        int a = 0, b = 0, c = 0;
        for (int i = 1; i < n; i++) {
           int n2 = dp[a] * 2, n3 = dp[b] * 3, n5 = dp[c] * 5;
           dp[i] = min(n2, min(n3, n5));
           /**
            * 注意不要用else, 因为当dp[i] = 6时,
            * a指针和b指针都要前移, 不然会产生重复的数字
            */
           if (dp[i] == n2) a++;
           if (dp[i] == n3) b++;
           if (dp[i] == n5) c++;
        }
        return dp[n-1];
    }
};