/* Leetcode 187.重复的DNA序列
 * 所有DNA都由一系列缩写为A,C,G和T的核苷酸组成，例如：“ACGAATTCCG”。在研究DNA时，识别DNA中的重复序列有时会对研究非常有帮助。
 * 编写一个函数来查找目标子串，目标子串的长度为10，且在DNA字符串s中出现次数超过一次。
 * 示例1：
 *  输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 *  输出：["AAAAACCCCC", "CCCCCAAAAA"]
 * 示例2:
 *  输入：s = "AAAAAAAAAAA"(11个'A')
 *  输出：["AAAAAAAAAA"]
 */
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string& s) {
        /* hashset用于去重和查找 */
        unordered_set<string> tmp, res;
        int l = s.length();
        if (l <= 10) return vector<string>();
        for (int i = 0; i + 10 <= l; i++) {
            string sub = s.substr(i, 10);
            if (tmp.find(sub) == tmp.end())
                /* 之前没出现过就加入到tmp */
                tmp.insert(sub);
            else
                /* 之前出现过, 重复的子串 */
                res.insert(sub);
        }
        return vector<string>(res.begin(), res.end());
    }
};