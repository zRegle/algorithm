/* Leetcode 79.单词搜索
 * 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 * 同一个单元格内的字母不允许被重复使用。
 * 示例:
 * board =
 * [
 *  ['A','B','C','E'],
 *  ['S','F','C','S'],
 *  ['A','D','E','E']
 * ]
 * 给定 word = "ABCCED", 返回 true.
 * 给定 word = "SEE", 返回 true.
 * 给定 word = "ABCB", 返回 false.(用过的字符不能再用)
 */
#include <iostream>
#include <vector>
using namespace std;

//简单的递归
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        int row = board.size(), col = board[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
                if (search(board, word, i, j, 0))
                    return true;
        }
        return false;
    }
private:
    bool search(vector<vector<char>>& board, string& word, int i, int j, int idx) {
        int row = board.size(), col = board[0].size();
        if (board[i][j] != word[idx])
            return false;
        else if (idx == word.size()-1)
            return true;
        board[i][j] = '\0'; //用过了, 置为空
        if (i > 0 && search(board, word, i-1, j, idx+1)) {
            return true;
        } else if (i < row-1 && search(board, word, i+1, j, idx+1)) {
            return true;
        } else if (j > 0 && search(board, word, i, j-1, idx+1)) {
            return true;
        } else if (j < col-1 && search(board, word, i, j+1, idx+1)) {
            return true;
        }
        board[i][j] = word[idx]; //回溯, 恢复为未用过的
        return false;
    }
};