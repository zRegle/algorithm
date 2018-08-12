//
// Created by Administrator on 2018/8/9.
//

#include <iostream>
#include <vector>
using namespace std;

int dp(vector<int> w, vector<int> v, vector<int> n, int c) {
    int num = w.size()-1;
    vector<vector<int>> dp(w.size());
    for (int i = 0; i < w.size(); i++) {
        vector<int> row((unsigned)c+1);
        dp.push_back(row);
        for (int j = 0; j <= c; ++j) {
            dp[i].push_back(0);
        }
    }
    for (int i = 1; i <= num; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (j >= w[i]) {
                int count = min(n[i], j/w[i]);
                dp[i][j] = dp[i-1][j];
                for (int k = 1; k <= count; ++k) {
                    //确定从第i件物品拿多少个价值最大
                    //区别于完全背包, 因为k这个计数变量, 所以我们得从dp[i-1]转移过来
                    dp[i][j] = max(dp[i][j], dp[i-1][j-k*w[i]]+k*v[i]);
                }
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    for (int m = 1; m <= num; ++m) {
        for (int i = 1; i <= c; ++i) {
            cout<<dp[m][i]<<" ";
        }
        cout<<endl;
    }
    int tmp = c;
    vector<int> used;
    //反推用了多少个物品
    for (int i = num; i >= 1; --i) {
        if (dp[i][c] != dp[i-1][c]) {
            int k = 1;
            while (true) {
                if (dp[i][tmp] == dp[i-1][tmp-k*w[i]]+k*v[i])
                    break;
                k++;
            }
            tmp -= k*w[i];
            used.push_back(k);
        } else {
            used.push_back(0);
        }
    }
    for (vector<int>::iterator it = used.begin(); it != used.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
    return dp[num][c];
}

int main() {
    int n, c;
    cin>>n>>c;
    vector<int> w(n+1);
    vector<int> v(n+1);
    vector<int> sn(n+1);
    for (int i = 1; i <= n; ++i) {
        cin>>w[i]>>v[i]>>sn[i];
    }
    cout<<dp(w, v, sn, c);
    return 0;
}