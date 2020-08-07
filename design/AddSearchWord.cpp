/* Leetcode 211. 添加与搜索单词 - 数据结构设计
 * 设计一个支持以下两种操作的数据结构：
 *  void addWord(word)
 *  bool search(word)
 * search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母'.'或'a'-'z'。'.'可以表示任何一个字母。
 */
#include <string>
using namespace std;

/* Leetcode 208的变种而已 */
struct TrieNode {
    TrieNode *children[26];
    bool end;

    TrieNode* get(char key) {
        return children[key - 'a'];
    }
    void put(char key, TrieNode *node) {
        children[key - 'a'] = node;
    }
    bool contains(char key) {
        return children[key - 'a'] != nullptr;
    }
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(const string& word) {
        auto cur = root;
        for (char c : word) {
            if (!cur->contains(c)) {
                auto node = new TrieNode();
                cur->put(c, node);
            }
            cur = cur->get(c);
        }
        cur->end = true;
    }
    
    /** Returns if the word is in the data structure.
     * A word could contain the dot character '.' to represent any one letter. */
    bool search(const string& word) {
        return search(root, word, 0);
    }

private:
    TrieNode *root;

    bool search(TrieNode* node, const string& word, int idx) {
        if (idx == word.length())
            return node->end;
        else {
            char c = word[idx++];
            if (c == '.') {
                /* '.'匹配任何字符, 搜索所有子节点, 有一个返回true就行 */
                bool flag = false;
                for (auto child : node->children) {
                    if (child != nullptr)
                        flag |= search(child, word, idx);
                }
                return flag;
            } else {
                if (!node->contains(c))
                    return false;
                else {
                    auto child = node->get(c);
                    return search(child, word, idx);
                }
            }
        }
    }
};