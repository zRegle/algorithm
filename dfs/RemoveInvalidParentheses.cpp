/* leetcode 301. Remove Invalid Parentheses
 * 给定一串字符串, 以最少的步骤去除其中的括号, 使其合法, 列出所有去除后的结果
 */
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

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

/* 经过剪枝的dfs, 两个剪枝思路:
 *  1.确定有多少个左右括号是错误的, 删除该数目即可保证删除数目最少且有效剪枝
 *  2.对于连续的括号, 删除任意一个都是的等价的
 */
class Solution2 {
public:
    vector<string> removeInvalidParentheses(string& s) {
        int err_left = 0, err_right = 0;
        /* 统计错误的左括号和右括号数目, 即我们要删除的括号数 */
        for (char c : s) {
            if (c == '(') err_left++;
            else if (c == ')') {
                if (err_left == 0) err_right++;
                else err_left--;
            }
        }
        string str;
        dfs(s, str, 0, err_left, err_right, 0, 0);
        return ans;
    }

private:
    vector<string> ans;
    /** 
     * dfs求解
     * 
     * \param s 原字符串
     * \param str 当前构建的字符串
     * \param idx 在原字符串的idx, 即当前dfs深度
     * \param err_left 当前还可以删除多少个左括号
     * \param err_right 当前还可以删除多少个右括号
     * \param cnt_left, cnt_right 对str当前的括号计数器, 实质上就是在递归过程中判断str是否合法
     */
    void dfs(string& s, string& str, int idx, 
            int err_left, int err_right, int cnt_left, int cnt_right) {
        /**
         * 1.str中右括号数目大于左括号, str不合法, 直接退出 
         * 2.当前已经不能够再删除括号了, 直接退出
         */
        if (cnt_right > 0 || err_left < 0 || err_right < 0) return;
        if (idx == s.length()) {
            if (cnt_left == 0 && cnt_right == 0) {
                /* 两个计数器都为0, 合法字符串 */
                ans.push_back(str);
            }
            return;
        }
        if (s[idx] == '(') {
            /* 统计有多少个连续的括号 */
            int k = idx;
            while (k < s.length() && s[k] == '(') k++;
            int cnt = k - idx;
            /* 一次性全部加上连续的括号, 曲折地实现了:
             * (1)多个连续的括号中, 只删除第一个括号
             * (2)删除的位置一定在上次删除的右边
             * 
             * 因为在回溯之后, 我们会按顺序的删除连续的括号
             * 如果不这样做, 那么比如这次递归我们在保留括号和删除括号中选择了保留
             * 在下次递归中, 我们会遇到在保留括号和删除括号中选择了删除
             * 这样就会造成"多个连续的括号中, 任意挑选一个删除", 从而造成了重复
             */
            str.append(cnt, '(');
            dfs(s, str, k, err_left, err_right, cnt_left + cnt, cnt_right);
            /* 回溯 */
            str.erase(str.length() - cnt, cnt);

            /* 删除当前括号 */
            dfs(s, str, idx + 1, err_left - 1, err_right, cnt_left, cnt_right);
        } else if (s[idx] == ')') {
            int k = idx;
            while (k < s.length() && s[k] == ')') k++;
            int cnt = k - idx;
            str.append(cnt, ')');
            int cl = max(0, cnt_left - cnt);
            int cr = max(0, cnt - cnt_left);
            dfs(s, str, k, err_left, err_right, cl, cr);
            str.erase(str.length() - cnt, cnt);
            
            dfs(s, str, idx + 1, err_left, err_right - 1, cnt_left, cnt_right);
        } else {
            /* 其他字符, 直接添加到str中 */
            str += s[idx];
            dfs(s, str, idx + 1, err_left, err_right, cnt_left, cnt_right);
            str.pop_back();
        }
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
 * 2.另外要注意一点, 假设s = "()()))", '^'表示第一个多余的')'的位置, 即i
 *                              ^
 *   如果我们每次都从0开始遍历前i个字符
 *   那么第一次for循环, 我们去除"()()))",  '^'表示去除的')'的位置, 变成"(()))",
 *                              ^                       
 *   第一次for循环的下一次递归, 去除的是"(()))", 变成"(())", 第一次for循环的整个过程结束
 *                                       ^
 *   第二次for循环, 我们去除"()()))", 变成"()())"
 *                            ^
 *   第二次for循环的下一次递归, 还是从0开始, 去除的是"()())", 变成了"(())"
 *                                                 ^
 *   产生了重复的结果, 并且遗漏了一种结果"()()"
 * 
 *   本质上来说, 我们容易在递归的过程中按不同的次序删除两次了两个相同位置的括号
 *   即第一种情况下第一次删除了第i个括号, 第二次删除了第j个括号
 *   第二种情况下, 第一次删除了第j个括号, 第二次删除了第i个括号
 *   两种情况产生的结果是一样的
 * 
 *   所以我们需要一个变量来记录: 在前i个字符中遍历时, 上一次去除的')'的位置
 *   此时第二次循环的下一次递归, 去除的就是"()())", 变成"()()"
 *                                          ^ 
 */
class Solution3 {
public:
    vector<string> res;

    vector<string> removeInvalidParentheses(string& s) {
        pair<char, char> p('(', ')');
        dfs(s, 0, 0, p);
        return res;
    }

    /* @params prev_i 表示当前s中, [0, i-1]是合法的
     * @params prev_j 上一次删除close bracket的位置
     */
    void dfs(string& s, int prev_i, int prev_j, pair<char, char>& p) {
        int count = 0;
        int i = prev_i;
        /* 确定第一个多余的close bracket */
        while (i < s.length() && count >= 0) {
            if (s[i] == p.first) count++;
            else if (s[i] == p.second) count--;
            i++;
        }
        if (count < 0) {
            /* close bracket过多 */
            i--; /* 回退while循环多出来的一步 */
            for (int j = prev_j; j <= i; j++) {
                /* 尝试在不同的地方删除多余的close bracket */
                /* s[j]是close bracket 并且 s[j]不是连续的close bracket
                 * 当j == prev_j时, j-1超出了[prev_j, i]的范围, 因此需要多加一个条件
                 */
                if (s[j] == p.second && (j == prev_j || s[j-1] != s[j])) {
                    string next = s;
                    next.erase(j, 1);
                    /* 删除了s[j]之后, next比s少一个字符, 
                     * 因此i和j都不需要+1, 因为刚好抵消掉了
                     */
                    dfs(next, i, j, p);
                }
            }
        } else {
            if (p.first == '(') {
                /* 此时可能open bracket比close bracket多, 需要复用代码递归处理这种情况, 需要先进行翻转
                 * 首先是pair的翻转, 我们就能直接复用'确定第一个多余的close bracket'的while循环
                 * 其次是字符串的翻转, 例如:"(()"
                 * 如果我们只进行pair的翻转二不进行字符串的翻转, 那么在第一次进入while循环, count就会直接变-1而退出
                 * 翻转后")((", 我们就能确定出错的'('
                 */
                pair<char, char> pp(')', '(');
                reverse(s.begin(), s.end());
                dfs(s, 0, 0, pp);
            } else {
                /* 已经生成了合法的字符串
                 * 进入检查是否有多余的open bracket之前进行了一次字符串的翻转 
                 * 此时需要再一次翻转才能得到结果
                 */
                reverse(s.begin(), s.end());
                res.push_back(s);
            }
        }
    }
};