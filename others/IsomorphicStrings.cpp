/* 205. 同构字符串
 * 给定两个字符串 s 和 t，判断它们是否是同构的。
 * 如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。
 * 所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。
 * 示例 1:
 *  输入: s = "egg", t = "add"
 *  输出: true
 * 示例 2:
 *  输入: s = "foo", t = "bar"
 *  输出: false
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string& s, string& t) {
        unordered_map<char, char> map; /* s->t的映射 */
        unordered_map<char, char>::iterator it;
        unordered_set<char> hasMapped; /* t是否之前被映射过 */
        for (int i = 0; i < s.length(); i++) {
            it = map.find(s[i]);
            if (it == map.end()) {
                if (hasMapped.find(t[i]) != hasMapped.end())
                    /* 没有s[i]的映射关系但是有t[i]的映射关系 */
                    return false;
                map[s[i]] = t[i];
                hasMapped.insert(t[i]);
            } else if (it->second != t[i])
                /* 不能映射到不同的字符上 */
                return false;
        }
        return true;
    }
};

/* 将s, t的各个字符都映射到对应的下标
 * 相当于把s, t都转化到一种共同的中间模式
 * 如果s,t映射后的结果不一致, 就不同构
 */
bool isIsomorphic(string& s, string& t) {
    int mapS[128] = {}, mapT[128] = {};
    for (int i = 0; i < s.length(); i++) {
        if (mapS[s[i]] != mapT[t[i]])
            return false;
        else {
            if (!mapT[s[i]]) {
                mapS[s[i]] = i + 1;
                mapT[t[i]] = i + 1;
            }
        }
    }
    return true;
}
