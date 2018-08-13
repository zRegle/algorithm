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
 * dp[i][j][k]代表走到棋盘的某一行时能够收集到最大的苹果数量
 * i, j, k分别代表三条路线, 且在每一行满足0 <= i < j < k <= m - 1, 在第一行和最后一行有i = j = k
 */

int dp(int** matrix, int n, int m) {
    int*** dp = new int**[m];   //上一行的结果
    int*** dp2 = new int**[m];  //当前行的结果
    for (int i = 0; i < m; ++i) {
        dp[i] = new int*[m];
        dp2[i] = new int*[m];
        for (int j = 0; j < m; ++j) {
            dp[i][j] = new int[m]();
            dp2[i][j] = new int[m]();
        }
    }
    //动规求解
    //TODO num是三条路线在某一步时横坐标和纵坐标的和
    //TODO 因为无论是向下还是向右, 三者的横坐标和纵坐标之和都是不变的, 用来控制每条路线的行动一致
    //TODO 一定要从1开始, m+n-2结束, 为什么从1开始还不是很明白?
    for (int num = 1; num <= m+n-2; ++num) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < m; ++k) {
                    int ay = num - i, by = num - j, cy = num - k;
                    if (ay < 0 || by < 0 || cy < 0 || ay >= n || by >= n || cy >= n) continue;
                    int apples_row = matrix[ay][i];
                    if (j != i)
                        apples_row += matrix[by][j];
                    if (k != j && k != i)
                        apples_row += matrix[cy][k];
                    int max = -1;
                    //确定到底是怎样走到当前的位置的
                    if (i > 0 && j > 0 && k > 0)
                        if (dp[i-1][j-1][k-1] > max)
                            max = dp[i-1][j-1][k-1];    //三条路径同时往右走
                    if (i > 0 && j > 0 && cy > 0)
                        if (dp[i-1][j-1][k] > max)
                            max = dp[i-1][j-1][k];  //前两条路径往右走,第三条往下走
                    if (i > 0 && by > 0 && cy > 0)
                        if (dp[i-1][j][k] > max)
                            max = dp[i-1][j][k];    //第一条往右走, 后两条往下走
                    if (ay > 0 && j > 0 && k > 0)
                        if (dp[i][j-1][k-1] > max)  //第一条往下走, 后两条往右走
                            max = dp[i][j-1][k-1];
                    if (ay > 0 && j > 0 && cy > 0)
                        if (dp[i][j-1][k] > max)
                            max = dp[i][j-1][k];    //第一条、第三条往下走, 第二条往右走
                    if (i > 0 && by > 0 && k > 0)
                        if (dp[i-1][j][k-1] > max)
                            max = dp[i-1][j][k-1];  //第一条、第三条往右走, 第二条往下走
                    if (ay > 0 && by > 0 && k > 0)
                        if (dp[i][j][k-1] > max)
                            max = dp[i][j][k-1];    //第一条、第二条往下走, 第三条往右走
                    if (ay > 0 && by > 0 && cy > 0)
                        if (dp[i][j][k] > max)
                            max = dp[i][j][k];  //三条都往下走
                    dp2[i][j][k] = max + apples_row;
                }
            }
        }
        int*** tmp = dp; dp = dp2; dp2 = tmp;
    }
    int max = dp[m-1][m-1][m-1];
    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            delete[](dp[k][i]);
            delete[](dp2[k][i]);
        }
        delete[](dp[k]);
        delete[](dp2[k]);
    }
    delete[](dp);
    delete[](dp2);
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