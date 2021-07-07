/**
 * Leetcode 1711. 大餐计数
 * 大餐 是指 恰好包含两道不同餐品 的一餐，其美味程度之和等于 2 的幂。
 * 你可以搭配 任意 两道餐品做一顿大餐。
 * 给你一个整数数组 deliciousness ，其中 deliciousness[i] 是第 i​​​​​​​​​​​​​​ 道餐品的美味程度，
 * 返回你可以用数组中的餐品做出的不同 大餐 的数量。结果需要对 109 + 7 取余。
 * 注意，只要餐品下标不同，就可以认为是不同的餐品，即便它们的美味程度相同。
 *  
 * 示例 1：
 *  输入：deliciousness = [1,3,5,7,9]
 *  输出：4
 *  解释：大餐的美味程度组合为 (1,3) 、(1,7) 、(3,5) 和 (7,9) 。
 *  它们各自的美味程度之和分别为 4 、8 、8 和 16 ，都是 2 的幂。
 * 
 * 示例 2：
 *  输入：deliciousness = [1,1,1,3,3,3,7]
 *  输出：15
 *  解释：大餐的美味程度组合为 3 种 (1,1) ，9 种 (1,3) ，和 3 种 (1,7) 。
 *  
 * 提示：
 *  (1)1 <= deliciousness.length <= 10^5
 *  (2)0 <= deliciousness[i] <= 2^20
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
using namespace std;

/**
 * 逐一比较数组的任意两对元素会超时
 * 可以先用哈希表记录数字的种类和出现的次数
 * 然后遍历每一种元素, 每一次遍历就枚举2的幂
 * 看是否有其他元素满足和当前元素相加等于2的幂
 */
class Solution0 {
public:
    int countPairs(vector<int>& deliciousness) {
        unordered_map<int, int> map;
        int maxVal = 0;
        /**
         * 统计每种数字出现的次数
         * 同时获取数组最大值
         */
        for (int x : deliciousness) {
            if (map.count(x) == 0)
                map[x] = 0;
            map[x]++;
            maxVal = max(maxVal, x);
        }
        int mod = (int)1e9 + 7;
        int maxSum = maxVal << 1; /* 数组两个元素相加最大不会超过这个值 */ 
        uint64_t ans = 0;
        /* 遍历每种数字 */
        for (auto it = map.begin(); it != map.end(); it++) {
            /* 枚举可能出现的2的幂 */
            for (int val = 1; val <= maxSum; val <<= 1) {
                int target = val - it->first;
                if (map.find(target) != map.end()) {
                    /* 例如: [1, 1, 1]
                     * 满足的组合有3种 => (3 * (3-1)) / 2
                     */
                    if (target == it->first)
                        ans = ans + (uint64_t)(map[target]-1) * map[target];
                    else
                        ans = ans + (uint64_t)map[target] * it->second;
                } 
            }
        }
        /**
         * 对于二元组(x, t)会分别计数两次(遍历x和遍历t),
         * 因此最后要利用容斥原理, 对重复计数的进行减半操作
         */
        ans = (ans >> 1) % mod;
        return ans;
    }
};

/**
 * 边遍历边统计
 * 由于遍历数组时，哈希表中已有的元素的下标一定小于当前元素的下标，
 * 因此任意一对元素之和等于 2 的幂的元素都不会被重复计算。
 */
class Solution1 {
public:
    int countPairs(vector<int>& deliciousness) {
        int maxSum = 1 << 22;
        int ans = 0, mod = (int)1e9 + 7;
        unordered_map<int, int> map;
        for (int x : deliciousness) {
            for (int val = 1; val <= maxSum; val <<= 1) {
                int target = val - x;
                int cnt = map.count(target) ? map[target] : 0;
                /* 一个x可以与之前的cnt个target组成大餐 */
                ans = (ans + cnt) % mod;
            }
            map[x]++;
        }
        return ans;
    }
};