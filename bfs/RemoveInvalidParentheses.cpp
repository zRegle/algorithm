#include <iostream>
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
 * 一个变量来保存符合要求的字符串的最长长度, 小于这个长度的都略过
 */

class Solution {
public:
    vector<string> removeInvalidParentheses(string& s) {
        vector<string> res;
        if (s.length() == 0) return res;
        queue<string> q;
        q.push(s);
        unorder_set<string> visit;
        visit.insert(s);
        int max_len = INT_MIN;
        while (!s.empty()) {
            string cur = q.front(); q.pop();
            int len = cur.length();
            if (isValid(cur)) {
                res.push_back(cur);
                max_len = len;
                continue;
            }
            if (len < max_len) continue;
            for (int i = 0; i < len; i++) {
                if (cur[i] == '(' || cur[i] == ')') {
                    string new_s = s;
                    new_s.erase(i, 1);
                    if (visit.find(new_s) == visit.end()) {
                        visit.insert(new_s);
                        queue.push(new_s);
                    }
                }
            }
        }
        return res;
    }

    bool isValid(string& str) {
        int cnt = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') cnt++;
            if (str[i] == ')' && cnt-- == 0) return false;
        }
        return cnt == 0;
    }
};
