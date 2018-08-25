#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * leetcode 301. Remove Invalid Parentheses
 * 给定一串字符串, 以最少的步骤去除其中的括号, 使其合法, 列出所有去除后的结果
 */

/**
 * 思路一:
 * 对应每个括号, 有去除和不去除两种选择, 通过适当的剪枝, 暴力dfs递归所有可能的情况
 * 最后判断是否合法并且步骤数
 *
 * 结果: 1888ms擦边勉强通过
 */
class Solution {
public:
    vector<string> res;
    int count = INT_MAX;

    vector<string> removeInvalidParentheses(string& s) {
        if (s.length() == 0) {
            res.emplace_back("");
            return res;
        }
        vector<bool> isRemoved(s.length(), false);
        remove(s, 0, isRemoved, 0);
        return res;
    }

    /**
     * 暴力dfs递归所有结果
     * @param s 原始字符串
     * @param idx 当前递归到的下标
     * @param isRemoved 标记数组
     * @param cnt 步骤数
     */
    void remove(string&s, int idx, vector<bool>& isRemoved, int cnt) {
        if (idx == s.length()) {
            tryAdd2Res(s, isRemoved, cnt);
            return;
        }
        if (s[idx] == ')' || s[idx] == '(') {
            vector<bool> keepCur(isRemoved);
            remove(s, idx+1, keepCur, cnt);

            if (cnt < count) {  //剪枝
                vector<bool> removeCur(isRemoved);
                removeCur[idx] = true;
                remove(s, idx+1, removeCur, cnt+1);
            }
        } else {
            vector<bool> keepCur(isRemoved);
            remove(s, idx+1, keepCur, cnt);
        }
    }

    //尝试着加入结果集
    void tryAdd2Res(string& s, vector<bool>& isRemoved, int cnt) {
        string afterRemoved;
        for (int i = 0; i < s.length(); ++i) {
            if (!isRemoved[i])
                afterRemoved += s[i];
        }
        auto it = find(res.begin(), res.end(), afterRemoved);   //确保结果唯一
        if (it == res.end() && isValid(afterRemoved)) {
            if (cnt < count) {
                //步骤更少, 则清楚之前的所有结果
                count = cnt;
                res.clear();
            }
            res.push_back(afterRemoved);
        }
    }

    //判断是否合法
    bool isValid(string& str) {
        stack<char> s;
        int idx = 0;
        while (idx < str.length()) {
            if (str[idx] == '(')
                s.push('(');
            else if (str[idx] == ')'){
                if (s.top() != '(')
                    return false;
                s.pop();
            }
            idx++;
        }
        return s.empty();
    }
};

/**
 * leetcode大神的0ms做法
 *
 * 首先, 假定字符串中是')'多出来了, 我们要去除多余的')'
 * 在原来的思路里, 我们在去除不同的括号时, 很容易就产生相同的结果
 * 这样就会造成不必要的递归, 使时间复杂度大大增加
 *
 * 1.例如: "())", 我们分别去除第一二个右括号时, 都只有一个结果"()"
 *   因此, 我们约定在一系列连续的')'中, 我们只去除第一个
 *
 * 2.例如: "(())())())", '^'表示第一个多余的')'的位置, 即i
 *                ^
 *   如果我们每次都从prev_i开始遍历前i个字符
 *   那么第一次去除, 我们去除的是"(())())())", '^'表示去除')'的位置
 *                                ^
 *   第二次for循环, 我们还是去除的还是"(())())())", 造成的重复的结果
 *                                     ^
 *   所以我们需要一个变量来记录: 在前i个字符中遍历时, 上一次去除的')'的位置
 */
class Solution2 {
public:
    vector<string> res;

    vector<string> removeInvalidParentheses(string& s) {
        if (s.length() == 0) {
            res.emplace_back("");
            return res;
        }
        auto p = new pair<char, char>('(', ')');
        remove(s, 0, 0, p);
        delete(p);
        return res;
    }

    void remove(string& s, int prev_i, int prev_j, pair<char, char>* p) {
        //第一层循环, 从上次结束的地方开始, 统计'(', ')'的数目
        for (int stack = 0, i = prev_i; i < s.length(); ++i) {
            if (s[i] == p->first) stack++;
            if (s[i] == p->second) stack--;
            if (stack < 0) {    //有多余的')'需要去除
                //第二层循环, 将字符串前i个字符合法化
                for (int j = prev_j; j <= i; ++j) {
                    //尝试着在前i个字符中的每个位置中去除多余的')'
                    //s[j-1] != p.second是确保一系列的')'中只去除第一个
                    if (s[j] == p->second && (j == prev_j || s[j-1] != p->second)) {
                        string afterRemoved = s;
                        afterRemoved.erase((unsigned int)j, 1);
                        remove(afterRemoved, i, j, p);
                    }
                }
                return; //直接返回, 因为在递归中, 会把[i+1, s.length()]的字符串合法化
            }
        }
        //关键的地方来了, 如果是'('多出来了呢?
        //将字符串反转, 利用相同的代码, 过一遍
        string rev = s;
        reverse(rev.begin(), rev.end());
        if (p->first == '(') {
            auto pp = new pair<char, char>(')', '(');
            remove(rev, 0, 0, pp);
            delete(pp);
        } else {
            //在进入删除多余的'('的递归之前, 我们已经将原始的字符串反转过一遍
            //当退出删除多余的'('的递归之后, 我们有反转了一遍, 得到原来的字符串
            //所以这里直接加入结果集
            res.push_back(rev);
        }
    }
};

int main() {
    string s = "(()))()())";
    Solution2 ss;
    auto res = ss.removeInvalidParentheses(s);
    for (auto& str : res)
        cout<<str<<endl;
    return 0;
}
