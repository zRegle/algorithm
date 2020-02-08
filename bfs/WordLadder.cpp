/* Leetcode 127.单词接龙
 * 给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：
 *  (1)每次转换只能改变一个字母。
 *  (2)转换过程中的中间单词必须是字典中的单词。
 * 说明:
 *  (1)如果不存在这样的转换序列，返回0。
 *  (2)所有单词具有相同的长度。
 *  (3)所有单词只由小写字母组成。
 *  (4)字典中不存在重复的单词。
 * 你可以假设 beginWord和endWord是非空的，且二者不相同。
 * 示例 1:
 *  输入:
 *   beginWord = "hit",
 *   endWord = "cog",
 *   wordList = ["hot","dot","dog","lot","log","cog"]
 *  输出: 5
 *  解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",返回它的长度 5。
 * 示例 2:
 *  输入:
 *   beginWord = "hit"
 *   endWord = "cog"
 *   wordList = ["hot","dot","dog","lot","log"]
 *  输出: 0
 *  解释: endWord "cog" 不在字典中，所以无法进行转换。
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int l1 = beginWord.length(), l2 = endWord.length();
        if (l1 != l2 || find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return 0;
        if (isOneChanged(beginWord, endWord)) return 2;
        queue<string> q; //BFS用到的队列
        q.push(beginWord);
        unordered_set<string> visited; //已经遍历过的单词
        visited.insert(beginWord);
        int minPath = 1;
        bool isFound = false;
        while (!q.empty() && !isFound) {
            int size = q.size(); 
            while (size--) { //将当前深度的全部节点pop出来
                string word = q.front(); q.pop();
                for (string& str : wordList) {
                    if (isOneChanged(word, str) && visited.find(str) == visited.end()) {
                        if (str == endWord) {
                            isFound = true;
                            goto nextLevel;
                        }
                        q.push(str);
                        visited.insert(str);
                    }
                }
            }
            nextLevel: minPath++; //遍历下一个深度
        }
        return isFound ? minPath : 0;
    }
    
    //dfs会超时, 因为搜了很多不必要的路径
    /**
     * dfs逐一试不同的路径
     * @param cur 当前变换到的单词
     * @param endWord 目标单词
     * @param level 当前深度
     * @param minPath 要返回的答案
     * @param visited 这条路径已经遍历过的单词
     * @param wordList 字典
     */
    void dfs(string& cur, string& endWord, int level, int& minPath,
            unordered_set<string>& visited, vector<string>& wordList) {
        if (cur == endWord) {
            minPath = min(level, minPath);
        } else {
            for (string& w : wordList) {
                if (isOneChanged(cur, w) && visited.find(w) == visited.end()) {
                    visited.insert(w);
                    dfs(w, endWord, level+1, minPath, visited, wordList);
                    visited.erase(w); //回溯
                }
            }
        }
    }
private:
    bool isOneChanged(string& s, string& t) {
        if (s.length() != t.length()) return false;
        bool flag = false;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != t[i]) {
                if (flag) return false;
                flag = true;
            }
        }
        return true;
    }
};

int main() {
    string s = "hit", t = "cog";
    vector<string> worList({"hot","dot","dog","lot","log","cog"});
    Solution sol;
    cout<<sol.ladderLength(s, t, worList);
    return 0;
}