#include <iostream>
using namespace std;

/*
 * leetcode 96
 * 给定一串序列1,2,...,n, 求由此序列构成的二叉搜索树有多少种
 * 例: n=3, 则有5种
 * 1         3     3      2      1
 *  \       /     /      / \      \
 *   3     2     1      1   3      2
 *  /     /       \                 \
 * 2     1         2                 3
 *
 * 思路:
 * 设dp[i]为长度为i时, 二叉搜索树的种数
 * [1, i]中的每个元素都可以作为根节点, 以j作为例子
 * 那么[1, j]需要放在j的左边, [j+1, i]放在右边
 * 两边各自构成二叉搜索树, 那么以长度为i, j为根节点的二叉搜索树有多少种呢?
 * 左边就是长度为j-1时, 二叉搜索树的种数; 右边实质上就相当于长度为i-j时, 二叉搜索树的种数
 * 所以长度为i, j为根节点的二叉搜索树的种数 = dp[j-1] * dp[i-j]
 * 故dp[i] = dp[1] * dp[i-1] + dp[2] * dp[i-2] + ... + dp[i-1] * dp[0] 
 */

class Solution {
public:
    int numTrees(int n) {
        int* dp = new int[n+1]();
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i] += dp[j-1] * dp[i-j];
            }
        }
        int cnt = dp[n];
        delete[](dp);
        return cnt;
    }
};

//递归版本
class Solution2 {
public:
    int numTrees(int n) {
        int* nums = new int[n+1]();
        nums[0] = nums[1] = 1;
        int ans = numTrees(n, nums);
        delete[](nums);
        return ans;
    }
private:
    int numTrees(int n, int* nums) {
        if (nums[n]) return nums[n];
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            cnt += numTrees(i-1) * numTrees(n-i);
        nums[n] = cnt;
        return cnt;
    }
}

int main() {
    Solution solution;
    cout<<solution.numTrees(3)<<endl;
    return 0;
}