#include <iostream>
#include <vector>
using namespace std;

/**
 * @param w 各个物品的重量
 * @param v 各个物品的价值
 * @param c 背包总容量
 * @return 能够获取到的最大价值
 */
int dp(vector<int>& w, vector<int>& v, int c) {
    int num = w.size();
    vector<vector<int>> dp(num+1, vector<int>(c+1));
    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= c; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= w[i-1]) {
                /* 第k个物品最多可以拿j/w[i-1]个, 一个一个遍历取最大值 */
                for (int k = 1; k * w[i-1] <= j; k++)
                    dp[i][j] = max(dp[i][j], dp[i-1][j-k*w[i-1]] + k*v[i-1]);
            }
        }
    }
    return dp[num][c];
}

/**
 * 上述方法是三重循环, 时间复杂度较高
 * 其实对于第i个物品, 我们拿多少个没必要多搞一个循环来判断
 * 回顾dp[i][j]的定义: 前i个物品中选择, 总容量为j, 能够获取到的最大价值
 * 那么我们完全可以用dp[i][j-w[i]]来替代第三层循环
 * 因为第一维的dp[i]就包含了选择第i个物品的含义在里面
 */
int time_optimize(vector<int> w, vector<int> v, int c) {
    int num = w.size();
    vector<vector<int>> dp(num+1, vector<int>(c+1));
    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= c; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= w[i-1])
                dp[i][j] = max(dp[i][j], dp[i][j-w[i-1]] + v[i-1]);
        }
    }
    return dp[num][c];
}

int space_optimize(vector<int>& w, vector<int>& v, int c) {
    int num = w.size();
    vector<int> dp(c+1);
    for (int i = 1; i <= num; i++) {
        for (int j = w[i-1]; j <= c; j++) {
            /**
             * 因为dp[i][j]只与它左边的值有关, 不与上一行有关
             * 所以这里不用像01背包那样倒序遍历
             */
            dp[j] = max(dp[j], dp[j-w[i-1]] + v[i-1]);
        }
    }
    return dp[c];
}