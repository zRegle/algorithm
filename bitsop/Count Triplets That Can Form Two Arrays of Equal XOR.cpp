/**
 * Leetcode 1442. 形成两个异或相等数组的三元组数目
 * 给你一个整数数组 arr 。
 * 现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。
 * a 和 b 定义如下：
 * a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 * b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * 注意：^ 表示 按位异或 操作。
 * 请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。
 *
 * 示例 1：
 *  输入：arr = [2,3,1,6,7]
 *  输出：4
 *  解释：满足题意的三元组分别是 (0,1,2), (0,2,2), (2,3,4) 以及 (2,4,4)
 */
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

/* 设xorsum(i, j) = arr[i] ^ arr[i+1] ^ ... ^ arr[j] */

/**
 * O(N^3)的方法
 * 假设xorsum(i, j-1)为a, xorsum(j, k)为b, xorsum(i, k)为c
 * 易知 c = a ^ b, 故有c ^ a = (a ^ b) ^ a = b
 * 如果 c ^ a = a, 那么三元组(i, j, k)则满足题目要求
 */
class Solution0 {
public:
    int countTriplets(vector<int>& arr) {
        int ans = 0, n = arr.size();
        for (int i = 0; i < n; i++) {
            int val0 = 0;
            for (int k = i; k < n; k++) {
                val0 ^= arr[k]; /* val0是[i, k]的异或结果 */
                int val1 = 0;
                for (int j = i; j < k; j++) {
                    val1 ^= arr[j]; /* val1是[i, j]的异或结果 */
                    if ((val0 ^ val1) == val1)
                        ans++;
                }
            }
        }
        return ans;
    }
};

/**
 * O(N^2)的做法
 * 由题意知: a = xorsum(i, j-1), b = xorsum(j, k)
 * 如果a == b, 则a ^ b = 0
 * 也就是说, 对于满足条件的三元组(i, j, k), xorsum(i, k) = a ^ b = 0
 * 因此如果xorsum(i, k) = 0, 对于任意j∈[i, k], 三元组(i, j, k)都满足条件
 */
class Solution1 {
public:
    int countTriplets(vector<int>& arr) {
        int ans = 0, n = arr.size();
        for (int i = 0; i < n; i++) {
            int xorSum = 0;
            for (int k = i; k < n; k++) {
                xorSum ^= arr[k];
                if (xorSum == 0)
                    /* [i, k]范围内任意的j都能组成满足题目要求的三元组 */
                    ans += k - i;
            }
        }
        return ans;
    }
};

/**
 * 时间O(N), 空间O(N)的做法
 *
 * 在Solution1的基础上, 对xorsum(i, k)进行拆分
 *   xorsum(i, k) = xorsum(0, i-1) ^ xorsum(0, k)
 * 我们将xorsum(i, k)表示成两个 前缀异或和 的异或和
 * 如果xorsum(i, k) = 0, 那么这两个 前缀异或和 的值一定相等
 * 我们设presum(u) = xorsum(0, u),
 *   如果 xorsum(i, k) = 0, 那么 presum(k) = presum(i-1)
 *
 * 前缀异或和可以使用O(n)的预处理时间全部计算得出，这样我们就可以略微修改Solution1的流程：
 * 用第一重循环枚举k, 而用第二重循环枚举i，只要:
 *   presum(k) = presum(i-1)，
 * 那么我们就找到了满足xorsum(i, k) = 0的二元组(i, k)，并用相同的方法进行计数即可。
 *
 * 这样的流程就有了优化的空间：对于每一个 k, 假设有i1, i2, ... , it均满足
 *   presum(k) = presum(i-1)
 * 那么这些二元组 (i1, k), (i2, k), ... , (it, k)对答案的贡献总和为：
 *   (k - i1) + (k - i2) + ... + (k - it) = t * k - (i1 + i2 + ... + it)
 *
 * 下面来看详细的代码
 */
class Solution2 {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        /**
         * 第一个哈希表, key -> presum(u), value -> presum(u)出现的次数
         * 其中有初始边界值 (0, 1)，表示异或和为 0（左边界，一个数都不选择）出现了 1 次
         */
        unordered_map<int, int> freq = {{0, 1}};
        /**
         * 第二个哈希表, key -> presum(u), value -> 出现的位置的下标之和, 代表上面公式的(i1 + ... + it)
         * 其中有初始边界值 (0, 0)，表示异或和为 0（左边界，一个数都不选择）对应的 i 值为 0
         */
        unordered_map<int, int> idxSum = {{0, 0}};
        int xorSum = 0, ans = 0;
        // 枚举 k
        for (int k = 0; k < n; ++k) {
            // 计算前缀异或和
            xorSum ^= arr[k];
            // 如果这个前缀异或和之前出现过，那么就找到了一些满足要求的三元组
            if (freq.find(xorSum) != freq.end()) {
                // 对应公式 t * k - sum(it)
                ans += freq[xorSum] * k - idxSum[xorSum];
            }
            // 更新前缀异或和的出现次数
            ++freq[xorSum];
            // 更新前缀异或和出现位置的下标之和
            // 注意 i-1 和 i 的关系，所以这里要额外增加 1
            idxSum[xorSum] += (k + 1);
        }
        return ans;
    }
};