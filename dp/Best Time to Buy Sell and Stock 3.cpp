#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/**
 * leetcode 123. Best Time to Buy and Sell Stock III
 * 给定一个数组, 它的第i个元素是一支给定的股票在第i天的价格。
 * 设计一个算法来计算你所能获取的最大利润. 你最多可以完成两笔交易.
 * 注意: 你不能同时参与多笔交易(你必须在再次购买前出售掉之前的股票)
 *
 * 输入: [3,3,5,0,0,3,1,4]
 * 输出: 6
 * 解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
 *     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3
 *     
 * 输入: [1,2,3,4,5]
 * 输出: 4
 * 解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
 *      注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出. 因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票
 */

/*
 * 思路:
 * 利用状态机进行动态规划:
 * init -> buy1 -> sell1 -> buy2 -> sell2(四个变量分别代表在对应状态时有的钱的最大值)
 * 我们的目的是到达sell2状态时, 能有最大值
 * init -> buy1 = 0 - price
 * buy1 -> sell1 = buy1 + price
 * sell1 -> buy2 = sell1 - price
 * buy2 -> sell2 = buy2 + price
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        int buy1 = INT_MIN, buy2 = INT_MIN, sell1 = 0, sell2 = 0;
        for (auto p : prices) {
            buy1 = max(buy1, -p);
            buy2 = max(buy2, sell1-p);
            sell1 = max(sell1, buy1+p);
            sell2 = max(sell2, buy2+p);
        }
        return sell2;
    }
};

int main() {
    Solution s;
    vector<int> price({6,1,3,2,4,7});
    cout<<s.maxProfit(price)<<endl;
    return 0;
}