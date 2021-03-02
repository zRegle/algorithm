/**
 * Leetcode 347. 前 K 个高频元素
 * 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
 * 
 * 示例 1:
 *  输入: nums = [1,1,1,2,2,3], k = 2
 *  输出: [1,2]
 * 示例 2:
 *  输入: nums = [1], k = 1
 *  输出: [1]
 *  
 * 提示：
 *  你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
 *  你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。
 *  题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
 *  你可以按任意顺序返回答案。
 */
#include <unordered_map>
#include <queue>
using namespace std;

/**
 * 直观思路:
 * map统计频率, 然后用最小堆来对频率进行排序, 保持堆的大小不超过k
 */
class Solution0 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        /* 自定义比较函数 */
        auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2) -> bool {
            return p1.second > p2.second;
        };
        /* 最小堆 */
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        /* 统计频率 */
        for (int x : nums) {
            if (map.find(x) == map.end())
                map[x] = 0;
            map[x]++;
        }
        /* 维护最小堆的大小不超过k */
        for (auto& p : map) {
            q.push(p);
            if (q.size() > k)
                q.pop();
        }
        vector<int> ans(k, 0);
        for (int i = 0; i < k; i++) {
            ans[i] = q.top().first;
            q.pop();
        }
        return ans;
    }
};

/**
 * 桶排序:
 * 思路类似, 还是先用map统计元素频率
 * 然后将元素频率作为下标, 对于出现频率不同的数字集合, 存入对应的数组下标即可
 */
class Solution1 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int x : nums) {
            if (map.find(x) == map.end())
                map[x] = 0;
            map[x]++;
        }
        /* 可能有不同数字出现相同频率, 因此要用二维数组 */
        auto buckets = vector<vector<int>>(nums.size() + 1, vector<int>());
        for (auto& p : map) {
            int fre = p.second;
            buckets[fre].push_back(p.first);
        }
        vector<int> ans;
        for (int i = nums.size(); i >= 0; i--) {
            if (buckets[i].empty()) continue;
            /* 判断当前最多可以push多少个元素 */
            int cnt = min(k - ans.size(), buckets[i].size());
            for (int j = 0; j < cnt; j++)
                ans.push_back(buckets[i][j]);
        }
        return ans;
    }
};

/**
 * 基于快速排序:
 * 首先, 还是统计频率, 然后基于频率排序
 * 对数组arr[l...r]做快速排序时, 将数组分为两个部分arr[l...q-1]和arr[q+1...j]
 * 使得任意x∈arr[l...q-1], 都有x <= arr[q]; 同理对于任意y∈arr[q+1...j], 都有y >= arr[q]
 *
 * 根据k与左侧数组arr[l...q-1]的长度(q - l)的大小关系:
 *  (1)k <= q - l, arr[l...r]前k大的值就是arr[l...q-1]的前k大的值
 *  (2)否则, arr[l...r]前k大的值 就等于左侧子数组全部元素，
 *  加上右侧子数组arr[q+1...r]中前 k - (q - l) 大的值
 *
 * 设处理长度为 N 的数组的时间复杂度为 f(N)。
 * 由于处理的过程包括一次遍历和一次子分支的递归，
 * 最好情况下，有 f(N) = O(N) + f(N/2)，根据master theorem，能够得到 f(N) = O(N)。
 */
class Solution2 {
public:
    void qsort(vector<pair<int, int>>& v, int start, int end, vector<int>& ret, int k) {
        int picked = rand() % (end - start + 1) + start;
        swap(v[picked], v[start]);

        int pivot = v[start].second;
        int index = start;
        for (int i = start + 1; i <= end; i++) {
            if (v[i].second >= pivot) {
                swap(v[index + 1], v[i]);
                index++;
            }
        }
        swap(v[start], v[index]);

        if (k <= index - start) {
            /* 左侧子数组的长度大于k, 前k大的值就在左侧子数组中 */
            qsort(v, start, index - 1, ret, k);
        } else {
            /* 否则为左侧数组全部元素加上右侧子数组的前k - (q - l)个元素 */
            for (int i = start; i <= index; i++) {
                ret.push_back(v[i].first);
            }
            if (k > index - start + 1) {
                qsort(v, index + 1, end, ret, k - (index - start + 1));
            }
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v: nums) {
            occurrences[v]++;
        }
        vector<pair<int, int>> values;
        /* 统计频率 */
        for (auto& kv: occurrences) {
            values.emplace_back(kv);
        }
        vector<int> ret;
        qsort(values, 0, values.size() - 1, ret, k);
        return ret;
    }
};