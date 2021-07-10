/**
 * Leetcode 981. 基于时间的键值存储
 * 创建一个基于时间的键值存储类 TimeMap，它支持下面两个操作：
 *  1. set(string key, string value, int timestamp)
 *     存储键 key、值 value，以及给定的时间戳 timestamp。
 *  2. get(string key, int timestamp)
 *     返回先前调用 set(key, value, timestamp_prev) 所存储的值，其中 timestamp_prev <= timestamp。
 * 
 * 如果有多个这样的值，则返回对应最大的  timestamp_prev 的那个值。
 * 如果没有值，则返回空字符串（""）。
 * 
 * 示例 1：
 *  输入：inputs = ["TimeMap","set","get","get","set","get","get"], 
 *       inputs = [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
 *  输出：[null,null,"bar","bar",null,"bar2","bar2"]
 *  解释：  
 *   TimeMap kv;   
 *   kv.set("foo", "bar", 1); // 存储键 "foo" 和值 "bar" 以及时间戳 timestamp = 1   
 *   kv.get("foo", 1);  // 输出 "bar"   
 *   kv.get("foo", 3); // 输出 "bar" 因为在时间戳 3 和时间戳 2 处没有对应 "foo" 的值，所以唯一的值位于时间戳 1 处（即 "bar"）   
 *   kv.set("foo", "bar2", 4);   
 *   kv.get("foo", 4); // 输出 "bar2"   
 *   kv.get("foo", 5); // 输出 "bar2"   
 * 
 * 示例 2：
 *  输入：inputs = ["TimeMap","set","set","get","get","get","get","get"], 
 *       inputs = [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
 *  输出：[null,null,null,"","high","high","low","low"]
 * 
 * 提示：
 *  (1)所有的键/值字符串都是小写的。
 *  (2)所有的键/值字符串长度都在 [1, 100] 范围内。
 *  (3)所有 TimeMap.set 操作中的时间戳 timestamps 都是严格递增的。
 *  (4)1 <= timestamp <= 10^7
 *  (5)TimeMap.set 和 TimeMap.get 函数在每个测试用例中将（组合）调用总计 120000 次。
 */
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * 嵌套map, 外层unordered_map保存key对应的value集合
 * 内层map保存时间戳对应的value
 *
 * 踩坑记录:
 * cppreference上写着
 *  lower_bound, upper_bound如果没找到符合条件的元素会返回end()
 * 但这是默认容器是从小到大排序的, 如果是从大到小排序, 没找到会返回begin()
 * 道理也很简单, 因为用的是二分搜索
 */
class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        if (map.find(key) == map.end())
            map[key] = std::map<int, string>();
        map[key][timestamp] = value;
    }

    string get(string key, int timestamp) {
        if (map.find(key) == map.end()) return "";
        /* 找到第一个大于给定时间戳的value */
        auto it = map[key].upper_bound(timestamp);
        if (it == map[key].begin())
            /* 第一个value的时间戳就大于给定时间戳
             * 没有小于等于给定时间戳的value
             * 返回空字符串 */
            return "";
        else if (it == map[key].end())
            /* 所有value的时间戳都小于给定时间戳
             * 返回最后一个value
             */
            return map[key].rbegin()->second;
        else
            /* it = 第一个大于给定时间戳的value
             * it-- = 第一个小于等于给定时间戳的value
             */
            return (--it)->second;
    }

private:
    /**
     * 内层map:
     *  key -> timestamp
     *  value -> 调用set时的value
     */
    unordered_map<string, map<int, string>> map;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */