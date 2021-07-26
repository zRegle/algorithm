/**
 * Leetcode 381. O(1) 时间插入、删除和获取随机元素 - 允许重复
 * 设计一个支持在平均 时间复杂度 O(1) 下， 执行以下操作的数据结构。
 * 注意: 允许出现重复元素。
 * 
 *  1.insert(val)：向集合中插入元素 val。
 *  2.remove(val)：当 val 存在时，从集合中移除一个 val。
 *  3.getRandom：从现有集合中随机获取一个元素。每个元素被返回的概率应该与其在集合中的数量呈线性相关。
 * 
 * 示例:
 *  // 初始化一个空的集合。
 *  RandomizedCollection collection = new RandomizedCollection();
 *  // 向集合中插入 1 。返回 true 表示集合不包含 1 。
 *  collection.insert(1);
 *  // 向集合中插入另一个 1 。返回 false 表示集合包含 1 。集合现在包含 [1,1] 。
 *  collection.insert(1);
 *  // 向集合中插入 2 ，返回 true 。集合现在包含 [1,1,2] 。
 *  collection.insert(2);
 *  // getRandom 应当有 2/3 的概率返回 1 ，1/3 的概率返回 2 。
 *  collection.getRandom();
 *  // 从集合中删除 1 ，返回 true 。集合现在包含 [1,2] 。
 *  collection.remove(1);
 *  // getRandom 应有相同概率返回 1 和 2 。
 *  collection.getRandom();
 */
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
using namespace std;

/**
 * 为了使得 O(1) 时间内能够随机获取一个元素，我们将每个数值（可以重复）存储在一个列表 nums 中。
 * 这样，获取随机元素时，只需要随机生成一个列表中的索引，就能够得到一个随机元素。
 *
 * 这样做的问题在于：列表中的随机删除并不是 O(1) 的。
 * 然而我们可以发现，列表中元素的顺序是无关紧要的，只要它们正确地存在于列表中即可。
 * 因此，在删除元素时，我们可以将被删的元素与列表中最后一个元素交换位置，随后便可以在O(1)时间内，从列表中去除该元素。
 * 这需要我们额外维护数值在列表中每一次出现的下标集合。对于数值 val 而言，记其下标集合为 IDX(val)
 *
 * 在删除时，我们找出 val 出现的其中一个下标 i，并将 nums[i] 与 nums[nums.length−1] 交换。
 * 随后，将 i 从 IDX(val) 中去除，并将 IDX(nums[nums.length−1]) 中原有的 nums.length−1 替换成 i。
 * 由于集合的每个操作都是 O(1) 的，因此总的平均时间复杂度也是 O(1) 的。
 */

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {

    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        v.push_back(val);
        map[val].insert(v.size()-1);
        return map[val].size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (map.find(val) == map.end())
            return false;
        /* 首先从val的下标集合中随便删除一个, 相当于删除一个val元素 */
        int idx = *map[val].begin();
        map[val].erase(idx);

        if (idx != v.size()-1) {
            /* 要删除val的下标不是vector的最后一个
             * 将最后一个元素与v[idx]交换 */
            int last = v.back();
            v[idx] = last;
            /* 更新最后一个元素的下标集合 */
            map[last].erase(v.size()-1);
            map[last].insert(idx);
        }

        if (map[val].empty())
            map.erase(val);
        /* 一个val元素已经被数组末端的元素覆盖了
         * 相当于删除了一个val元素
         * 最后再pop_back数组末端
         */
        v.pop_back();
        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        return v[random() % v.size()];
    }

private:
    unordered_map<int, unordered_set<int>> map;
    vector<int> v;
    default_random_engine random;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */