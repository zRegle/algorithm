#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;

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
        return true;
    }
};
