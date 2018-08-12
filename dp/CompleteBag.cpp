//
// Created by Administrator on 2018/8/7.
//

#include <iostream>
using namespace std;

int item_num = -1;
int bag_size = -1;

int dp(int* weight, int* value, int* count) {
    int** dp = new int*[item_num + 1];
    for (int i = 0; i < item_num + 1; ++i) {
        dp[i] = new int[bag_size + 1]();
    }
    for (int j = 0; j <= bag_size; ++j) {
        dp[1][j] = j / weight[1];
    }
    for (int i = 1; i <= item_num; ++i) {
        for (int j = 1; j <= bag_size; ++j) {
            if (j >= weight[i] && dp[i][j - weight[i]] + value[i] > dp[i - 1][j]) {
                dp[i][j] = dp[i][j - weight[i]] + value[i];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    int tmp = bag_size;
    int max_value = dp[item_num][bag_size];
    for (int k = item_num; k >= 1; --k) {
        while (tmp >= weight[k]) {
            if (dp[k][tmp] != dp[k - 1][tmp]) {
                count[k]++;
                tmp -= weight[k];
            } else {
                break;
            }
        }
    }
    for (int l = 0; l < item_num + 1; ++l) {
        delete[](dp[l]);
    }
    delete[](dp);
    return max_value;
}

int dp2(int* weight, int* value, int* count) {
    int* dp = new int[bag_size+1]();
    for (int i = 1; i <= item_num; ++i)
        for (int j = bag_size; j >= 1; --j)
            for (int k = 1; k <= j/weight[i]; ++k)
                dp[j] = max(dp[j], dp[j-k*weight[i]]+k*value[i]);
    int tmp = bag_size;
    for (int l = 1; l <= bag_size; ++l) {
        cout<<dp[l]<<" ";
    }
    cout<<endl;
    for (int i = item_num; i >= 1; --i) {
        int k = 0;
        for (; k <= tmp/weight[i];) {
            if (dp[tmp] == dp[tmp-k*weight[i]]+k*value[i]) {
                k++;
            }
        }
        count[i] = k-1;
        tmp -= (k-1)*weight[i];
    }
    return dp[bag_size];
}

int main() {
    cin>>item_num>>bag_size;
    int* weight = new int[item_num + 1]();
    int* value = new int[item_num + 1]();
    int* count = new int[item_num + 1]();
    for (int i = 1; i <= item_num; ++i) {
        cin>>weight[i]>>value[i];
    }
    int max_value = dp2(weight, value, count);
    for (int i = 1; i <= item_num; i++) {
        cout<<count[i]<<" ";
    }
    cout<<endl;
    cout<<"max_value: "<<max_value<<endl;
    delete[](weight); delete[](value);
    return 0;
}