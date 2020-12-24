/* Leetcode 123.买股票的最佳时机3
 * 给定一个数组，它的第i个元素是一支给定的股票在第i天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成2次交易。
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 示例 1:
 *  输入: [3,3,5,0,0,3,1,4]
 *  输出: 6
 *  解释: 在第4天（股票价格 = 0）的时候买入，在第6天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
 *      随后，在第7天（股票价格 = 1）的时候买入，在第8天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
 */
#include <vector>
using namespace std;


/*设global(i,j)为在前i天完成j次交易能够得到的最大利润，local(i,j)为在前i天完成j次交易并且最后一次卖出股票是在第i天能够得到的最大利润；
 * prices(i)表示股票在第i天的价格。那么有递推关系式：
 *  local(i,j)=max{global(i-1,j-1),local(i-1,j)}+prices(i)-prices(i-1)
 *  global(i,j)=max{local(i,j),global(i-1,j)}
 * (1)对于global(i,j)来说，我们可以选择在第i天卖出股票，即local(i,j)。
 *    或者我们可以在第i天之前就完成j次交易，即global(i-1,j).
 *    那么明显有:global(i,j)=max{local(i,j),global(i-1,j)}
 * (2)设prices(i)-prices(i-1)为diff。对于local(i,j)来说，我们有两种选择：
 *    (2.1)在第i-1天完成j-1次交易，并在当天买入股票，然后在第i天卖出，相当于global(i-1,j-1) + diff。
 *    (2.2)在前i-1天完成j-1次交易，并且在第m天卖出股票第j-1次，在第n天买入股票第j次(1 ≤ m, n< i-1且m ≤ n)，最后在第i天卖出股票。
 *    那么这实际上相当于local(i-1,j)+diff，因为假设local(i-1,j)是在第k天卖出的(1 ≤ k ≤ i-1)，现在我们变成在第i天卖出，实际上不会增加交易的次数，
 *    最后再加上第i天卖出能赚的利润就可以了。
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int days = prices.size();
        vector<vector<int>> global(days+1, vector<int>(3, 0));
        vector<vector<int>> local(days+1, vector<int>(3, 0));
        for (int i = 1; i <= days; i++) {
            int diff = i >= 2 ? prices[i-1] - prices[i-2] : 0;
            for (int j = 1; j <= 2; j++) {
                local[i][j] = max(global[i-1][j-1], local[i-1][j]) + diff;
                global[i][j] = max(local[i][j], global[i-1][j]);
            }
        }
        return global[days][2];
    }
};

//space complexity: O(1)
int max_profit(vector<int>& prices) {
    if (prices.empty()) return 0;
    int days = prices.size();
    int global[3] = {0}, local[3] = {0};
    for (int i = 1; i <= days; i++) {
        int diff = i >= 2 ? prices[i-1] - prices[i-2] : 0;
        for (int j = 2; j >= 1; j--) {
            local[j] = max(global[j-1], local[j]) + diff;
            global[j] = max(local[j], global[j]);
        }
    }
    return global[2];
}