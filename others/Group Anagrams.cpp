/* Leetcode 49 字母异位词分组
 * 给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。
 * 示例
 * 输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
 * 输出
 * [
 *  ["ate","eat","tea"],
 *  ["nat","tan"],
 *  ["bat"]
 * ]
 */

#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//维护一个map, key是string, value是vector<string>
//将字符串按字典排序, 然后对比字符串是否相等
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> m;
        map<string, vector<string>>::iterator it;
        for (string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            if ((it = m.find(key)) != m.end()) {
                it->second.push_back(s);
            } else {
                vector<string> v;
                v.push_back(s);
                m[key] = v;
            }
        }
        vector<vector<string>> res(m.size());
        for (auto& p : m)
            res.push_back(p.second);
        return res;
    }
};