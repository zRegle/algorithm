#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;

/*
 * leetcode 301. Remove Invalid Parentheses
 * 给定一串字符串, 以最少的步骤去除其中的括号, 使其合法, 列出所有去除后的结果
 *
 * 思路:
 * 典型的bfs结构, 用队列来进行bfs, 一个unordered_set(hash实现)来保存已经遍历过的字符串
 * 一个变量表示是否得到合法的字符串, 如果是则不进行下一层的遍历
 */

class Solution {
public:
    vector<string> removeInvalidParentheses(string& s) {
        vector<string> res;
        queue<string> q;
        q.push(s);
        unordered_set<string> visit;
        visit.insert(s);
        bool found = false;
        while (!s.empty()) {
            string cur = q.front(); q.pop();
            if (isValid(cur)) {
                found = true;
                res.push_back(cur);
            }
            if (found) continue;
            for (int i = 0; i < cur.length(); i++) {
                if (cur[i] == '(' || cur[i] == ')') {
                    string next = cur;
                    next.erase(i, 1);
                    if (visit.find(next) == visit.end()) {
                        visit.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        return res;
    }

    bool isValid(string& str) {
        int cnt = 0;
        for (char c : str) {
            if (c == '(') cnt++;
            else if (c == ')' && cnt-- == 0) return false;
        }
        return cnt == 0;
    }
};

/* 不利用set来进行去重的方法
 * 1.对于连续的括号而言, 只删除第一个
 * 2.保证下一次删除的括号的位置一定在上次删除括号位置的右边
 */
class Solution2 {
public:
    vector<string> removeInvalidParentheses(string& s) {
        vector<string> res;
        queue<pair<string, int>> q;
        q.push({s, 0});
        bool found = false;
        while (!s.empty()) {
            auto cur = q.front(); q.pop();
            string str = cur.first;
            int last_remove = cur.second;
            if (isValid(str)) {
                found = true;
                res.push_back(str);
            }
            if (found) continue;
            //从上一次删除的位置开始
            for (int i = last_remove; i < str.length(); i++) {
                if (str[i] == '(' || str[i] == ')') {
                    //对于连续的括号而言, 只删除第一个
                    if (i == 0 || str[i - 1] != str[i]) {
                        string next = str;
                        next.erase(i, 1);
                        //删除一个字符后, i就自动变成下一次开始遍历的位置了
                        q.push({next, i});
                    }
                }
            }
        }
        return res;
    }

    bool isValid(string& str) {
        int cnt = 0;
        for (char c : str) {
            if (c == '(') cnt++;
            else if (c == ')' && cnt-- == 0) return false;
        }
        return cnt == 0;
    }
};