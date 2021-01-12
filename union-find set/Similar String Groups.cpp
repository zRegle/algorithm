/**
 * Leetcode 839. 相似字符串组
 * 如果我们交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，
 * 那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。
 *
 * 例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "
 * rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。
 *
 * 总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。
 * 注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。
 * 形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
 * 我们给出了一个字符串列表 A。列表中的每个字符串都是 A 中其它所有字符串的一个字母异位词。
 * 请问 A 中有多少个相似字符串组？
 *
 * 示例1：
 *  输入：["tars","rats","arts","star"]
 *  输出：2
 *
 * 示例2：
 *  输入：["blw", "bwl", "lwb"]
 *  输出：1
 *  解释："blw"与"bwl"相似, 而"bwl"又与"lwb"相似, 所以是同一个相似组
 */
#include <vector>
#include <string>
using namespace std;

/* 本质就是求连通分量, 相似的字符串就用边连起来, 并查集就完事了 */

inline bool isSimilar(const string& s1, const string& s2) {
    int diff = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) diff++;
        if (diff > 2) return false;
    }
    return true;
}

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        int size = strs.size();
        father.resize(size); rank.resize(size);
        for (int i = 0; i < size; i++) {
            father[i] = i;
            rank[i] = 1;
        }
        int cnt = size;
        for (int i = 0; i < size-1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (isSimilar(strs[i], strs[j]))
                    if (merge(i, j))
                        cnt--;
            }
        }
        return cnt;
    }

private:
    vector<int> father;
    vector<int> rank;

    int find(int x) {
        return x == father[x] ? x : (father[x] = find(father[x]));
    }

    bool merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) return false;
        if (rank[x] >= rank[y])
            father[y] = x;
        else
            father[x] = y;
        if (rank[x] == rank[y])
            rank[x]++;
        return true;
    }
};