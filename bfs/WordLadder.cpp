#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <map>
using namespace std;

/* leetcode 126. Word Ladder II
 * 给定初始字符串begin和目标字符串end, 一个字符串数组list
 * list中的字符串, begin, end都相等; begin ≠ end; list中没有重复的字符串
 * 求出从begin变化到end的所有步数最小的序列串
 * 变化规则:
 * 1.每次变化只能变化一个字符
 * 2.变换的结果必须存在于list中
 * 
 * 我的思路:
 * bfs, 利用队列存储序列串, 利用map记录变化到某个字符需要多少步和某个字符是否已经被变化得到过
 * 结果超时了(估计是map的操作比较耗时)
 */

class Solution {
public:
    vector<vector<string>> ladderLength(string& beginWord, string& endWord, vector<string>& wordList) {
        vector<vector<string>> res;

        queue<vector<string>> paths;
        paths.push(vector<string>({beginWord}));

        map<string, int> m;
        m.insert(pair<string, int>(beginWord, 1));

        int min_level = INT_MAX;

        while (!paths.empty()) {
            vector<string> path = paths.front(); //当前处理的序列串
            paths.pop();

            int size = path.size(); //比最短符合要求的序列要长, 略过
            if (size > min_level) continue;

            string last = path.back();  //当前序列的最后一个变化得到的字符
            if (last == endWord) {
                res.push_back(path);
                min_level = size;   //确定了最短的长度
            } else {
                for (string& word : wordList) { //遍历字符串数组
                    if (canTransfer(last, word)) {
                        auto iter = m.find(word);
                        if (iter == m.end()) {
                            //若该字符串还未被变化得到
                            vector<string> new_path(path);  //深拷贝一份新的序列串
                            new_path.push_back(word);
                            m.insert(pair<string, int>(word, size+1));
                            paths.push(new_path);
                        } else {
                            if (iter->second == size+1) {   //若从具有相同长度的不同的序列变化到同一个字符
                                vector<string> new_path(path);
                                new_path.push_back(word);
                                paths.push(new_path);
                            }
                        }
                    }
                }
            }
        }
        return res;
    }

    //判断是否可以从s转化到t
    bool canTransfer(string& s, string& t) {
        int cnt = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != t[i])
                cnt++;
        }
        return cnt == 1;
    }
};

int main() {
    string s = "hit", t = "cog";
    string a[] = {"hot","dot","dog","lot","log","cog"};
    vector<string> v(a, a+7);
    Solution ss;
    auto res = ss.ladderLength(s, t, v);
    for (vector<string>& path :res) {
        for (string& str : path)
            cout<<str<<" ";
        cout<<endl;
    }
    return 0;
}
