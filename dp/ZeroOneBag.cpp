//
// Created by Administrator on 2018/8/7.
//

#include <iostream>
using namespace std;

int dp(int* weight, int* value, bool* used, int item_num, int bag_size) {
    int** dp = new int*[item_num + 1];
    for (int i = 0; i < item_num + 1; ++i) {
        dp[i] = new int[bag_size + 1]();
    }
    for (int i = 1; i <= item_num; ++i) {
        for (int j = 1; j <= bag_size; ++j) {
            if (j >= weight[i])
                dp[i][j] = max(dp[i - 1][j - weight[i]] + value[i], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    int max_value = dp[item_num][bag_size];
    for (int k = item_num; k >= 1; --k) {
        if (bag_size >= weight[k]) {
            if (dp[k][bag_size] != dp[k - 1][bag_size]) {
                used[k] = true;
                bag_size -= weight[k];
            }
        }
    }
    for (int l = 0; l < item_num + 1; ++l) {
        delete[](dp[l]);
    }
    delete[](dp);
    return max_value;
}

//降维方法
int dp2(int* w, int* v, bool* used, int n, int c) {
    int* dp = new int[c+1]();
    /* 理解:
     * 1.降维的动机是什么:
     * 当我们在计算dp[i][j]的时候, 我们只需要用到dp[i-1]那一行的内容, 所以除了上一行的数据我们可以完全舍弃掉,
     * 那么我们完全可以用未更新的当前行来存储上一行的内容, 实现降维。
     * 2.为什么第二层循环倒着来:
     * 回到最初的状态状态转移方程, 在计算dp[i][j]的时候, 需要用到上一行的dp[i-1][j]和dp[i-1][j-w[i]]
     * 我们要用未更新的当前行来存储上一行的内容, 那么它们对应的位置就在dp[j]和dp[j-w[i]]
     * 如果我们不倒着来, 那么dp[j-w[i]]势必要比dp[j]先修改, 那么上一行的值就不见了
     * 所以要倒着来
     */
    for (int i = 1; i <= n; ++i) {
        for (int j = c; j >= 1; --j) {
            if (j >= w[i])
                dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
                //等式右边的dp[j]相当于dp[i-1][j]
                //dp[j-w[i]]+v[i]相当于dp[i-1][j-w[i]]+v[i]
        }
    }
    for (int k = n; k >= 1; ++k) {
        if (c >= w[k]) {
            if (dp[k] == dp[k-w[k]])
                used[k] = true;
            c -= w[k];
        }
    }
    return dp[c];
}

int main() {
    int n, size;
    cin>>n>>size;
    int* weight = new int[n + 1]();
    int* value = new int[n + 1]();
    bool* used = new bool[n + 1]();
    for (int i = 1; i <= n; ++i) {
        cin>>weight[i]>>value[i];
    }
    int max_value = dp(weight, value, used, n, size);
    for (int i = 1; i <= n; i++) {
        if (used[i])
            cout<<i<<" ";
    }
    cout<<"\n"<<max_value<<endl;
    delete[](weight); delete[](value); delete[](used);
    return 0;
}