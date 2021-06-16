#include <vector>
#include <numeric>
#include <climits>
using namespace std;

/* dp方法参考dp文件夹
 * 数学方法参考math文件夹 */

/* 最初思路: 有点丑陋 */
class Solution0 {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        int sum = accumulate(piles.begin(), piles.end(), 0);
        mem.resize(n, vector<int>(n));
        return dfs(0, n-1, piles) > (sum >> 1);
    }

private:
    vector<vector<int>> mem;
    int dfs(int i, int j, vector<int>& piles) {
        if (i >= piles.size() || j < 0 || i > j) return 0;
        if (i == j) return piles[i];

        if (mem[i][j] != 0)
            return mem[i][j];

        int ans = 0, sum;
        /* A拿i, B拿j */
        sum = piles[i] + dfs(i+1, j-1, piles);
        ans = max(ans, sum);
        /* A拿i, B拿i+1 */
        sum = piles[i] + dfs(i+2, j, piles);
        ans = max(ans, sum);
        /* A拿j, B拿i */
        sum = piles[j] + dfs(i+1, j-1, piles);
        ans = max(ans, sum);
        /* A拿j, B拿j-1 */
        sum = piles[j] + dfs(i, j-2, piles);
        ans = max(ans, sum);

        mem[i][j] = ans;
        return ans;
    }
};

/* 更加优雅的思路 */
class Solution1 {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        mem.resize(n, vector<int>(n, INT_MIN));
        return dfs(0, n-1, piles) > 0;
    }

private:
    /* 记忆化数组 */
    vector<vector<int>> mem;
    /* [i, j]区间内先手, 能够最多赢对手多少个石子
     * 注意, 这里先手选的人在每次递归都不一样 */
    int dfs(int i, int j, vector<int>& piles) {
        if (i == j)
            return piles[i];
        if (mem[i][j] != INT_MIN)
            return mem[i][j];
        /**
         * Alex先手选piles[i]
         * 那么Lee在[i+1, j]区间内先手选, 最多能赢Alex的石子数为
         *  dfs(i+1, j, piles) (ps: 可能为负数)
         * 那么只要piles[i] > dfs(i+1, j, piles)
         * 则Alex在这个[i, j]区间内先手选必胜
         *
         * Alex先手选piles[j]同理
         */
        int left = piles[i] - dfs(i+1, j, piles);
        int right = piles[j] - dfs(i, j-1, piles);
        int res = max(left, right);
        mem[i][j] = res;
        return res;
    }
};