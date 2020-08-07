/* Leetcode 212.单词搜索2
 * 给定一个二维网格board和一个字典中的单词列表words，找出所有同时在二维网格和字典中出现的单词。
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 * 同一个单元格内的字母在一个单词中不允许被重复使用。
 * 示例:
 * 输入:
 * words = ["oath","pea","eat","rain"] and board =
 * [
 *   ['o','a','a','n'],
 *     ^   ^
 *   ['e','t','a','e'],
 *         ^   ^   ^ 
 *   ['i','h','k','r'],
 *         ^
 *   ['i','f','l','v']
 * ]
 * 输出:["eat","oath"] (各自的搜索路径用'^'标注出来了)
 */
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;


/* 思路:
 * 对输入的words构建一棵前缀树
 * 然后从board的不同cell出发, 递归查找能否在前缀树中找到对应的单词
 * 优势在于如果在递归过程中, 某个前缀不可能在前缀树中出现, 即可停止递归
 */
struct TrieNode {
    TrieNode* links[26];
    bool end;
    bool contains(char c) {
        return links[c - 'a'] != nullptr;
    }
    TrieNode* get(char c) {
        return links[c - 'a'];
    }
    void put(char c, TrieNode* n) {
        links[c - 'a'] = n;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        row = board.size();
        if (row == 0) return vector<string>();
        col = board[0].size();
        /* 构建前缀树 */
        for (string& w: words) {
            auto cur = root;
            for (char c : w) {
                if (!cur->contains(c))
                    cur->put(c, new TrieNode());
                cur = cur->get(c);
            }
            cur->end = true;
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                string str;
                dfs(root, str, i, j, board);
            }
        }
        return ans;
    }

private:
    int row, col;
    TrieNode* root = new TrieNode();
    vector<string> ans;

    void dfs(TrieNode* node, string& str, int i, int j, vector<vector<char>>& board) {
        if (node->end) {
            ans.push_back(str);
            /* 已经匹配到words中的一个, 把这个word从前缀树中删除, 去重 */
            node->end = false;
            /* TODO
             * 这里有一个地方可以优化, 当这个node是叶子节点时
             * 我们可以将它从前缀树中删除, 直接返回
             * 这样做的好处在于可以减少树的规模, 减少后续递归所需的时间
             * 然而leetcode的实际测试并没有太大的变化, 因此不写进来
             * 具体实现方法参考英文版leetcode 08/07/2020 23:18的提交记录
             */
        }
        if (i < 0 || j < 0 || i == row || j == col) return;
        if (board[i][j] == '#') return;

        char c = board[i][j];
        if (!node->contains(c)) 
            /* 当前str + c的前缀不可能匹配到words里的单词
             * 提前停止递归, 返回
             */
            return;
        
        board[i][j] = '#';
        str += c;

        auto child = node->get(c);
        int vertical[] = {1,-1,0,0}, horizontal[] = {0,0,1,-1};
        for (int k = 0; k < 4; k++) {
            int newRow = i + vertical[k];
            int newCol = j + horizontal[k];
            dfs(child, str, newRow, newCol, board);
        }
        /* 回溯复原 */
        str.pop_back();
        board[i][j] = c;
    }
};

/* 暴力dfs, 居然过了
 * time: beat 5.03%
 * memory: beat 98.04%
 */
class Solution1 {
public:
    int row, col;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        /* 测试集的words里有重复的单词, 所以要用set */
        unordered_set<string> set;
        row = board.size();
        if (row == 0) return vector<string>();
        col = board[0].size();
        /* 与前缀树做法的差别在于
         * 对于每个word都要进行两层的循环
         * 而前缀树只需要进行一次两层循环即可
         */
        for (string& w : words) {
            /* 尝试不同的起点 */
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (dfs(0, w, i, j, board))
                        set.insert(w);
                }
            }
        }
        return vector<string>(set.begin(), set.end());
    }

    bool dfs(int idx, string& word, int i, int j, vector<vector<char>>& board) {
        if (idx == word.length()) return true;
        if (i < 0 || j < 0 || i == row || j == col) return false;

        if (word[idx] == board[i][j]) {
            /* 标记已经访问过了 */
            board[i][j] = '\0';
            /* up, down, left, right
             * 只要有一个true就不dfs其他位置了
             */
            int vertical[] = {1,-1,0,0}, horizontal[] = {0,0,1,-1};
            for (int k = 0; k < 4; k++) {
                int newRow = i + vertical[k];
                int newCol = j + horizontal[k];
                if (dfs(idx+1, word, newRow, newCol, board)) {
                    board[i][j] = word[idx];
                    return true;
                }
            }
        }
        return false;
    }
};