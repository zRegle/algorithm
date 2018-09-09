#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * leetcode 139. Word Break
 * 给定一个字符串和一个字典, 问该字符串是否可由字典中的单词组成(单词可重复使用)
 * 例如:
 * s = "applepenapple", wordDict = ["apple", "pen"] => true
 * s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"] => false
 */

/*
 * bfs方法:
 * 可以看成一个图的问题, 顶点的值是字符串中的第i个字符, 边是字典中的单词
 * 我们的目标是在图中寻找一条路径, 能否从初始顶点走到最终的顶点
 * 例如: s = "leetcode", wordDict = ["leet", "code"]
 * 那么我们有路径0->4->8
 */
class Solution2 {
public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        //初始化queue和visit
        queue<int> bfs; bfs.push(0);
        int len = s.length();
        bool* visit = new bool[len+1]; fill_n(visit, len, false);
        int mLen = max_len(wordDict);
        while (!bfs.empty()) {
            int start = bfs.front(); bfs.pop();
            for (int i = 1; i <= mLen; i++) {
                //从起点出发, 尝试构造字典中的单词
                string w = s.substr((unsigned int)start, (unsigned int)i);
                if (find(wordDict.begin(), wordDict.end(), w) != wordDict.end()) {
                    if (start+i == s.length())  //到达终点
                        return true;
                    else {
                        //判断新起点是否遍历过
                        if (!visit[start+i]) {
                            visit[start+i] = true;
                            bfs.push(start+i);
                        }
                    }
                }
            }
        }
        delete[](visit);
        return false;
    }

private:
    //统计字典里单词的最长长度
    int max_len(vector<string>& wordDict) {
        int len = -1;
        for (string& w : wordDict) {
            len = max(len, (int)w.length());
        }
        return len;
    }
};

int main() {
    string str = "bccdbacdbdacddabbaaaadababadad";
    vector<string> wordDict
            ({"cbc","bcda","adb","ddca","bad",
             "bbb","dad","dac","ba","aa","bd",
             "abab","bb","dbda","cb","caccc","d",
             "dd","aadb","cc","b","bcc","bcd","cd",
             "cbca","bbd","ddd","dabb","ab","acd",
             "a","bbcc","cdcbd","cada","dbca","ac",
             "abacd","cba","cdb","dbac","aada","cdcda",
             "cdc","dbc","dbcb","bdb","ddbdd","cadaa",
             "ddbc","babb"});
    Solution1 s;
    cout<<s.wordBreak(str, wordDict)<<endl;
    return 0;
}