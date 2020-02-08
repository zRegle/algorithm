/* Leetcode 134.加油站
 * 在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 * 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。
 * 你从其中的一个加油站出发，开始时油箱为空。
 * 如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。
 */
#include <iostream>
#include <vector>
using namespace std;

//O(n²)的做法, 尝试每一个起始站
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        const int n = gas.size();
        for (int i = 0; i < n; i++) {
            int j = i, cur = 0;
            bool flag = true;
            do {
                cur += gas[j];
                if (cur >= cost[j]) {
                    cur -= cost[j];
                    j = (j + 1) % n;
                } else {
                    flag = false;
                    break;
                }
            } while (j != i);
            if (flag) return i;
        }
        return -1;
    }
};

//O(n)算法
class Solution1 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        const int n = gas.size();
        //totalGas: 所有加油站能够提供的汽油总量
        //从idx出发到第i站时, 剩余的汽油
        int curGas = 0, totalGas = 0, idx = 0;
        for (int i = 0; i < n; i++) {
            curGas += gas[i] - cost[i];
            totalGas += gas[i] - cost[i];
            if (curGas < 0) {
                //如果从上一个idx出发无法到达第i站
                //那就把i+1作为新的出发站
                //这个算法最终能够保证从idx出发能到达终点站
                //至于怎么保证从第0站到达第idx站, 看官方解释：
                //https://leetcode-cn.com/problems/gas-station/solution/jia-you-zhan-by-leetcode/
                curGas = 0;
                idx = i + 1;
            }
        }
        //如果totalGas < totalCost, 返回-1
        return totalGas < 0 ? -1 : idx;
    }
};