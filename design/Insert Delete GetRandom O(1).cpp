#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        /* 用哈希表来判断是否已存在, 数组末尾增加一个元素，哈希表记录{元素:索引}映射关系 */
        if (map.find(val) == map.end()) {
            int size = v.size();
            map[val] = size;
            v.push_back(val);
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        /* 用哈希表来判断元素是否存在, 把数组最后一个元素取下来顶替被删除的元素，更新映射关系 */
        if (map.find(val) != map.end()) {
            int idx = map[val];
            /* 最后一个元素顶替被删除的元素 */
            map[v.back()] = idx;
            std::swap(v.back(), v[idx]);
            /* 删除元素 */
            v.pop_back();
            map.erase(val);
            return true;
        }
        return false;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return v[rand() % v.size()];
    }

private:
    /* element -> index的映射 */
    unordered_map<int, int> map;
    vector<int> v;
};