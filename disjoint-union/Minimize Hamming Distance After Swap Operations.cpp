/**
 * Leetcode 1722. 执行交换操作后的最小汉明距离
 * 给你两个整数数组 source 和 target ，长度都是 n 。还有一个数组 allowedSwaps ，
 * 其中每个 allowedSwaps[i] = [ai, bi] 表示你可以交换数组 source 中下标为 ai 和 bi（下标从 0 开始）的两个元素。
 * 注意，你可以按 任意 顺序 多次 交换一对特定下标指向的元素。
 *
 * 相同长度的两个数组 source 和 target 间的 汉明距离 是元素不同的下标数量。
 * 形式上，其值等于满足 source[i] != target[i] （下标从 0 开始）的下标 i（0 <= i <= n-1）的数量。
 *
 * 在对数组 source 执行 任意 数量的交换操作后，返回 source 和 target 间的 最小汉明距离 。
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "DSU.h"
using namespace std;

/**
 * 根据题意不难注意到，如果 1,2 之间可以交换，2,3 之间可以交换，
 * 那么即使 [1,3]未出现在 allowedSwaps 数组中，1,3 之间也是可以交换的。
 * 此时可以把[1,2,3]看做一个连通分量
 */
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int len = source.size();
        DSU dsu(len);
        for (auto& e : allowedSwaps)
            /* 构建好连通分量 */
            (void)dsu.merge(e[0], e[1]);
        /**
         * 对于变量s来说:
         *  key -> 连通分量的root元素在source中的下标
         *  value -> 对应连通分量里的所有元素
         *
         * 对于变量t来说:
         *  key -> source中连通分量root元素的下标
         *  value -> source中root元素所在的连通分量里的所有元素,
         *          它们在source中的下标构成一个集合INDEX
         *          所有{target[i], i ∈ INDEX}构成的集合
         *
         *  即: 对于source来说, 用map维护各个连通分量对应位置元素的集合
         *  需要做的是看看这些元素在target对应位置中是否存在即可
         *
         *  例如:
         *      source = [6,12,24]
         *      target = [12,6,48]
         *      allowedSwaps = [[0,1],[1,2]]
         *  我们知道, source中[6,12,24]是一个连通分量, 那么它们的顺序可以任意交换
         *  [6,12,24]的下标分别为[0,1,2], 我们只需要判断target中下标为[0,1,2]的元素集合中, 是否能找到[6,12,24]即可
         *
         *  (set是为了加速查找, multiset是因为可以允许有重复元素存在)
         */
        unordered_map<int, vector<int>> s;
        unordered_map<int, unordered_multiset<int>> t;
        for (int i = 0; i < len; i++) {
            int father = dsu.find(i);
            s[father].push_back(source[i]);
            t[father].insert(target[i]);
        }
        int ans = 0;
        for (int i = 0; i < len; i++) {
            if (dsu.find(i) != i) continue; /* 不是root元素, 跳过 */
            for (int x : s[i]) {
                if (t[i].find(x) == t[i].end())
                    /* source中的元素在target中找不到, 距离加一 */
                    ans++;
                else
                    /* source中的元素在target中找到, 需要把它删除
                     * 不然source中有两个相同元素而target中只有一个就出错了
                     */
                    t[i].erase(t[i].find(x));
            }
        }
        return ans;
    }
};