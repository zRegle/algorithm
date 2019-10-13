#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

/** 
 * leetcode 126 word ladder 2
 * 给定两个单词begin, end和一个单词数组wordList, 定义如下变化规则
 * 1.每次变化只能变化单词中的一个字母
 * 2.变化出来的单词必须存在于wordList中
 * 求出所有从begin变化到end的最短单词序列
 * (wordList中的单词, begin, end的长度都相同; wordList中不存在重复的单词; begin和end不一样)
 * 
 * 例如：
 * begin = "hit"
 * end = "cog"
 * wordList = ["hot", "lot", "dot", "dog", "log", "cog"]
 * 结果:
 * ["hit", "hot", "dot", "dog", "cog"]
 * ["hit", "hot", "lot", "log", "cog"]
 *
 */

/*
 * 我的思路:
 * 典型bfs结构, 队列中存的是变化的路径, 而不是单词
 *
 * 结果: 39/39 Test Case, 1504ms擦边通过
 */
class Solution {
public:
    vector<vector<string>> findLadders(string& beginWord, string& endWord, vector<string>& wordList) {
        vector<vector<string>> res; //结果集合
        queue<vector<string>> paths;    //bfs用的队列
        unordered_map<string, int> map; //用于确认某个单词是否被遍历过, 以及变化到这个单词的最小步骤
        paths.push(vector<string>({beginWord}));
        map.insert(pair<string, int>(beginWord, 1));
        int min_level = INT_MAX;    //用于确定最短变化路径
        while (!paths.empty()) {
            vector<string> path = paths.front(); paths.pop();
            int size = path.size();
            if (size > min_level) continue;
            string last = path.back();
            if (last == endWord) {
                res.push_back(path);
                min_level = size;
                continue;
            }
            for (string& word : wordList) {
                if (canTransfer(last, word)) {
                    auto it = map.find(word);
                    if (it == map.end()) {
                        //该单词未被遍历过
                        vector<string> new_path(path);
                        new_path.push_back(word);
                        map.insert(pair<string, int>(word, size+1));
                        paths.push(new_path);
                    } else {
                        //该单词遍历过
                        if (it->second == size+1) {
                            //该单词可以从数条具有相同长度的不同路径得到    
                            vector<string> new_path(path);
                            new_path.push_back(word);
                            paths.push(new_path);
                        }
                    }
                }
            }
        }
        return res;
    }

    //判断t和s是否只相差一个字符
    bool canTransfer(string& t, string& s) {
        int cnt = 0;
        for (int i = 0; i < t.length(); i++) {
            if (t[i] != s[i] && ++cnt > 1)
                return false;
        }
        return true;
    }
};

int main() {
    string s = "hit", t = "cog";
    string a[] = {"hot","dot","dog","lot","log","cog"};
    vector<string> v(a, a+7);
    Solution ss;
    auto res = ss.findLadders(s, t, v);
    for (vector<string>& path :res) {
        for (string& str : path)
            cout<<str<<" ";
        cout<<endl;
    }
    return 0;
}