/* Leetcode 77.组合
 * 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
 * 示例
 * 输入: n = 4, k = 2
 * 输出:
 * [
 *  [2,4],
 *  [3,4],
 *  [2,3],
 *  [1,2],
 *  [1,3],
 *  [1,4]
 * ]
 */
#include <vector>
using namespace std;

//没啥好说的, dfs走起来
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> nums;
        dfs(n, k, 1, ans, nums);
        return ans;
    }

    void dfs(int n, int k, int cnt, vector<vector<int>>& ans, vector<int>& nums) {
        if (nums.size() == k)
            ans.emplace_back(nums);
        else {
            //注意，这里有剪枝操作，如果我们把for循环的终止条件写成i <= n，
            //如果nums已经选择到 [1,4,5] 或者 [2,4,5] 或者 [3,4,5] ，后序的代码就没有必要执行，继续走也不能发现新的满足题意的组合。
            //程序干了类似于下面事情，其实有很多步骤是多余的：
            //选择了 [1,4,5] 以后， 5 弹出 [1,4,5] 成为 [1,4] , 4 弹出 [1,4] 成为 4 ，
            //然后 5 进来，成为 [1,5]，再进来发现 for 循环都进不了（因为没有可选的元素），然后 5 又弹出，接着 1 弹出。
            //比如n=6, k=4, 此时nums.size() == 1, 我们还需要选3个元素, 如果此时i=5, 我们就可以确定不需要再继续dfs了,
            for (int i = cnt; i <= n-(k-nums.size())+1; i++) {
                nums.push_back(i);
                dfs(n, k, i+1, ans, nums);
                nums.pop_back();
            }
        }
    }
};