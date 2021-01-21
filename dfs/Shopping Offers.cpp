/**
 * Leetcode 638.大礼包
 * 在LeetCode商店中， 有许多在售的物品。
 * 然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。
 * 现给定每个物品的价格，每个大礼包包含物品的清单，以及待购物品清单。请输出确切完成待购清单的最低花费。
 * 每个大礼包的由一个数组中的一组数据描述，最后一个数字代表大礼包的价格，其他数字分别表示内含的其他种类物品的数量。
 * 任意大礼包可无限次购买。
 *
 * 示例 1:
 *  输入: [2,5], [[3,0,5],[1,2,10]], [3,2]
 *  输出: 14
 *  解释:
 *   有A和B两种物品，价格分别为¥2和¥5。
 *   大礼包1，你可以以¥5的价格购买3A和0B。
 *   大礼包2， 你可以以¥10的价格购买1A和2B。
 *   你需要购买3个A和2个B， 所以你付了¥10购买了1A和2B（大礼包2），以及¥4购买2A。
 * 示例 2:
 *  输入: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
 *  输出: 11
 *  解释:
 *   A，B，C的价格分别为¥2，¥3，¥4.
 *   你可以用¥4购买1A和1B，也可以用¥9购买2A，2B和1C。
 *   你需要买1A，2B和1C，所以你付了¥4买了1A和1B（大礼包1），以及¥3购买1B， ¥4购买1C。
 *   你不可以购买超出待购清单的物品，尽管购买大礼包2更加便宜。
 *
 * 说明:
 *  (1)最多6种物品， 100种大礼包。
 *  (2)每种物品，你最多只需要购买6个。
 *  (3)你不可以购买超出待购清单的物品，即使更便宜。
 */
#include <vector>
#include <numeric>
#include <map>
using namespace std;

/* 也可以用dp, 类似于完全背包问题 */

/* dfs暴搜 + 记忆化 */
class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        if (map.find(needs) != map.end())
            return map[needs];
        int cnt = price.size();
        /**
         * 计算待购物清单下, 单个单个购买item需要多少钱
         * inner_product: 用于计算两个vector的内积, 必须保证两个vector的大小一致
         * 前两个参数是定义第1个vector的输入迭代器，第3个参数是确定第2个vector的开始输入迭代器，第4个参数是和的初值
         */
        int cost = inner_product(needs.begin(), needs.end(), price.begin(), 0);
        for (const auto& s : special) {
            bool flag = true;
            /* 判断是否购买超出待购清单的物品 */
            for (int i = 0; i < cnt; i++) {
                if (needs[i] < s[i]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) continue;
            /* 待购清单减去礼包 */
            for (int i = 0; i < cnt; i++)
                needs[i] -= s[i];
            cost = min(cost, s.back() + shoppingOffers(price, special, needs));
            /* 回溯 */
            for (int i = 0; i < cnt; i++)
                needs[i] += s[i];
        }
        map[needs] = cost;
        return cost;
    }

private:
    /**
     * 记忆化搜索
     * key -> 待够清单
     * value -> 最小需要花多少钱
     */
    map<vector<int>, int> map;
};