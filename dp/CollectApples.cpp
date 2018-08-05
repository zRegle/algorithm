//
// Created by Administrator on 2018/8/5.
//

#include <iostream>
using namespace std;

/*
 * 一个棋盘内有n x m个格子, 每个格子有一定数量的苹果
 * 从棋盘的左上角走到右下角, 再从左下角返回右上角, 最后再走到右下角
 * 求最多能拿到多少个苹果
 *
 * 思路:
 * 可以看成三次从左上角走到右下角, 且三条路线互不相交(除了左上角和右下角), 利用动态规划求解
 * dp[i][j][k]代表走到棋盘的第y行时能够收集到最大的苹果数量
 * i, j, k分别代表三条路线, 且在每一行满足0 <= i < j < k <= m - 1, 在第一行和最后一行有i = j = k
 */

int dp(int** matrix, int n, int m) {
    int*** dp = new int**[m];
    for (int i = 0; i < m; ++i) {
        dp[i] = new int*[m];
        for (int j = 0; j < m; ++j) {
            dp[i][j] = new int[m]();
        }
    }
    dp[0][0][0] = matrix[0][0];
    //动规求解
    //一行一行地走,第一行最多只能收集左上角的苹果, 所以从第二行开始遍历
    for (int row = 1; row < n; ++row) {
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                for (int k = j + 1; k < m; ++k) {
                    //循环控制变量要满足i < j < k

                    //首先把每条路线到达该行的格子里的苹果捡了
                    dp[i][j][k] += matrix[row][i] + matrix[row][j] + matrix[row][k];
                    //第一条路线可以从它自己的左边移动过来
                    dp[i][j][k] += dp[i-1][j][k];
                    //第二条路线可以从它自己的左边移动过来
                    dp[i][j][k] += dp[i][j-1][k];
                    //第三条路线可以从它自己的左边移动过来
                    dp[i][j][k] += dp[i][j][k-1];
                }
            }
        }
    }
    int max = dp[m-1][m-1][m-1];
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            delete[](dp[k][i]);
        }
        delete[](dp[k]);
    }
    delete[](dp);
    return max;
}

int main() {
    int n, m;
    cin>>n>>m;
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m]();
        for (int j = 0; j < m; ++j) {
            cin>>matrix[i][j];
        }
    }
    cout<<dp(matrix, n, m);
    for (int k = 0; k < n; ++k) {
        delete[](matrix[k]);
    }
    delete[](matrix);
    return 0;
}