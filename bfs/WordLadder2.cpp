#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
 * 结果: TLE了
 */
class MyTry {
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

//利用DFS生成某一条路径, 利用BFS生成所有路径的
class Solution {
public:
    unordered_map<string, vector<string>> children; //某个单词能够通过一部转化得到的所有单词, 即某个节点的所有孩子节点
    unordered_map<string, int> distance; //到达这个单词所需的最短距离
    vector<vector<string>> ans; //结果数组
    unordered_set<string> dict; //字典集合

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        dict.insert(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return ans;   //字典中没有endWord, 直接返回
        dict.insert(beginWord);
        bfs(beginWord, endWord);
        vector<string> curPath;
        dfs(beginWord, endWord, curPath);
        return ans;
    }
private:
    //bfs生成当前深度节点的所有子节点
    void bfs(string& start, string& end) {
        //初始化字典中所有单词的子节点数组
        for (const string& s : dict) {
            children[s] = vector<string>();
        }
        queue<string> q;
        q.push(start);
        distance[start] = 0;
        bool isFound = false;
        while (!q.empty()) {
            int cnt = q.size();
            for (int i = 0; i < cnt; i++) {
                string cur = q.front(); q.pop(); //当前单词
                int curDistance = distance[cur];    //当前深度
                auto v = getNeighbors(cur); //获取该单词的所有子节点单词
                for (const string& s : v) {
                    children[cur].push_back(s); //插入到当前单词对应的pair中中
                    if (distance.find(s) == distance.end()) {
                        //如果这个子节点没有被遍历过
                        distance[s] = curDistance + 1;
                        if (s == end)
                            isFound = true;
                        else
                            q.push(s);
                    }
                }
            }
            if (isFound) break;
        }
    }

    //dfs生成搜索路径
    void dfs(string& cur, string& end, vector<string>& curPath) {
        curPath.push_back(cur);
        if (end == cur)
            ans.push_back(curPath);
        else {
            for (string& next : children[cur]) {
                if (distance[next] == distance[cur] + 1)
                    //剪枝, 如果节点在之前的某一层已经被遍历过了, 那么我们就不需要继续递归下去
                    dfs(next, end, curPath);
            }
        }
        //回溯
        curPath.pop_back();
    }

    //将word里的每一个逐一换成'a'-'z'里的字符, 看字典里是否存在对应的单词
    vector<string> getNeighbors(string& word) {
        vector<string> result;
        for (int i = 0; i < word.length(); i++) {
            char tmp = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == tmp) continue;
                word[i] = c;
                if (dict.find(word) != dict.end())
                    result.push_back(word);
            }
            word[i] = tmp;
        }
        return result;
    }
};

//只用BFS求解
class Solution2 {
public:
    vector<vector<string>> findLadders(string& beginWord, string& endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> ans;
        if (dict.find(endWord) == dict.end()) return ans;
        unordered_set<string> visited;  //记录哪些单词之前的层数中遍历过
        queue<vector<string>> paths;
        paths.push(vector<string>({beginWord}));
        visited.insert(beginWord);
        bool isFound = false;
        while (!paths.empty()) { //遍历下一层
            int size = paths.size();
            //记录在当前层数循环中有哪些单词被遍历了
            unordered_set<string> subVisited;
            for (int i = 0; i < size; i++) {
                auto p = paths.front(); paths.pop();
                string word = p.back();
                for (int j = 0; j < word.length(); j++) {
                    char tmp = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (tmp == c) continue;
                        word[j] = c;
                        //字典中存在对应单词, 并且这个单词在之前的层数中没有被遍历过
                        if (dict.find(word) != dict.end() && visited.find(word) == visited.end()) {
                            vector<string> newPath(p); //新的路径
                            p.push_back(word);
                            if (word == endWord) {
                                isFound = true;
                                ans.push_back(newPath);
                            }
                            paths.push(newPath);
                            //不能直接加入到visited中, 因为在这一层中可能存在不同路径到达同一个单词
                            //而visited是记录在之前层数中遍历到哪些单词
                            subVisited.insert(word);
                        }
                    }
                    word[j] = tmp;
                }
            }
            if (isFound) break;
            visited.insert(subVisited.begin(), subVisited.end());
        }
        return ans;
    }
};

int main() {
    string s = "hit", t = "cog";
    vector<string> v({"hot","dot","dog","lot","log","cog"});
    Solution sol;
    auto res = sol.findLadders(s, t, v);
    for (vector<string>& path : res) {
        for (string& str : path)
            cout<<str<<" ";
        cout<<endl;
    }
    return 0;
}