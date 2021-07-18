/**
 * 面试题 10.02. 变位词组
 * 编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。变位词是指字母相同，但排列不同的字符串。
 * 注意：本题相对原题稍作修改
 * 示例:
 *  输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
 *  输出:
 *   [
 *    ["ate","eat","tea"],
 *    ["nat","tan"],
 *    ["bat"]
 *   ]
 * 说明：
 *  (1)所有输入均为小写字母。
 *  (2)不考虑答案输出的顺序。
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * 对每个字符串排序, 变位词排序完后是一样的
 * 因此将排序完后的字符串作为key类归类变位词
 */
class Solution0 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> map;
        for (string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            map[key].push_back(s);
        }
        ans.resize(map.size());
        auto it = map.begin();
        for (int i = 0; i < ans.size(); i++, it++) {
            ans[i] = it->second;
        }
        return ans;
    }
};

/**
 * 也可以以每个字母出现的次数拼接成字符串作为key
 */
class Solution1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> map;
        for (string& s : strs) {
            int cnt[26] = {0};
            for (char c : s) cnt[c - 'a']++;
            string key;
            for (int x : cnt)
                key += to_string(x) + '@';
            map[key].push_back(s);
        }
        ans.resize(map.size());
        auto it = map.begin();
        for (int i = 0; i < ans.size(); i++, it++) {
            ans[i] = it->second;
        }
        return ans;
    }
};