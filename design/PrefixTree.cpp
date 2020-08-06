/* Leetcode 208.实现 Trie (前缀树)
 * 实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。
 * 你可以假设所有的输入都是由小写字母 a-z 构成的。
 * 保证所有输入均为非空字符串。
 */
#include <string>
#include <unordered_map>
using namespace std;

/* 我的实现, 没看到可以假设全是小写字母输入, 所以比较繁琐 */
struct TrieNode {
    bool end; /* 是否可以为终止节点 */
    unordered_map<char, TrieNode*> children;
    TrieNode(bool val) : end(val) {}
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode(false);
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        int idx = 0;
        /* dfs返回的结果有两种可能:
         * 1.word已经包含树中, 可能是作为前缀也可能是作为整个单词, 那么下面的for循环将不会执行
         * 2.word的一部分已经作为前缀包含在树中, 执行for循环
         */
        TrieNode* ptr = dfs(root, word, idx);

        /* 处理dfs返回结果的第二种, 将剩下的字符加到树中 */
        TrieNode* cur, *prev = ptr;
        for (int i = idx; i < word.length(); i++) {
            cur = new TrieNode(false);
            prev->children[word[i]] = cur;
            prev = cur;
        }
        /* 无论循环是否执行, 最后一个节点一定可以是终止节点 */
        prev->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        int idx = 0;
        TrieNode* ptr = dfs(root, word, idx);
        /* 已经搜索完整个词并且最后停在了叶子节点, 代表搜索成功 */
        return idx == word.length() && ptr->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int idx = 0;
        (void)dfs(root, prefix, idx);
        /* 已经搜索完整个词 */
        return idx == prefix.length();
    }

    ~Trie() {
        deleteTree(root);
    }

private:
    TrieNode* root;

    void deleteTree(TrieNode* cur) {
        for (auto p : cur->children)
            deleteTree(p.second);
        delete cur;
    }

    /**
     * dfs搜索某个字符串
     * @param node 当前开始节点
     * @param prefix 要搜索的字符串
     * @param cur 进行到字符串的哪个位置
     * @return 停止在哪就返回哪个节点
     *
     * 返回值和cur传引用的设计是为了方便"插入"操作
     */
    TrieNode* dfs(TrieNode* node, string& str, int& cur) {
        if (cur == str.length())
            return node;
        auto it = node->children.find(str[cur]);
        if (it != node->children.end()) {
            cur++;
            return dfs(it->second, str, cur);
        }
        /* 搜索失败, 返回当前节点, 同样保留了cur的值 */
        return node;
    }
};

/* 官方解答, 思路大体一致 */
struct Node {
    Node* links[26];
    bool end;
    bool contains(char c) {
        return links[c - 'a'] != nullptr;
    }
    Node* get(char c) {
        return links[c - 'a'];
    }
    void put(char c, Node* n) {
        links[c - 'a'] = n;
    }
};

class Trie1 {
public:
    Node *root;
    /** Initialize your data structure here. */
    Trie1() {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        auto cur = this->root;
        for (char c : word) {
            if (!cur->contains(c))
                cur->put(c, new Node());
            cur = cur->get(c);
        }
        cur->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto node = searchPrefix(word);
        return node != nullptr && node->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto node = searchPrefix(prefix);
        return node != nullptr;
    }

private:
    Node* searchPrefix(string& word) {
        auto cur = root;
        for (char c : word) {
            if (cur->contains(c))
                cur = cur->get(c);
            else
                return nullptr;
        }
        return cur;
    }
};