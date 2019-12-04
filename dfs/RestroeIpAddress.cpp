/* Leetcode 93.ip地址复原
 * 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 * 示例:
 *  输入: "25525511135"
 *  输出: ["255.255.11.135", "255.255.111.35"]
 */
#include <vector>
#include <string>
using namespace std;

//这题本来正常做要用回溯算法, 但奈何边界条件太多, 非常讨厌, 所以就用"讨厌"的方法做了
class Solution {
public:
    vector<string> restoreIpAddresses(string& s) {
        vector<string> ret;
        string ans;
        for (int a = 1; a <= 3; a++)
            for (int b = 1; b <= 3; b++)
                for (int c = 1; c <= 3; c++)
                    for (int d = 1; d <= 3; d++)
                        if (a + b + c + d == s.length()) {
                            int A = stoi(s.substr(0, a));
                            int B = stoi(s.substr(a, b));
                            int C = stoi(s.substr(a + b, c));
                            int D = stoi(s.substr(a + b + c, d));
                            if (A <= 255 && B <= 255 && C <= 255 && D <= 255)
                                if ((ans = to_string(A) + "." + to_string(B) + "." + to_string(C) + "." + to_string(D)).length() == s.length() + 3)
                                    ret.emplace_back(ans);
                        }
        return ret;
    }
};

//正常的做法
class Solution2 {
public:
    vector<string> restoreIpAddresses(string& s) {
        backtrack(s, 0, 0);
        return ans;
    }
private:
    vector<string> ans;
    /**
     * dfs + 回溯
     * @param s 当前的字符串
     * @param start dfs的深度, 开始截取ip段的位置
     * @param cnt 当前字符串'.'的个数
     */
    void backtrack(string& s, int start, int cnt) {
        if (cnt == 3) {
            string sub = s.substr(start);
            if (isValid(sub))
                ans.emplace_back(s);
        } else {
            for (int i = 1; i <= 3; i++) {
                if (start + i < s.size()) { //插入'.'的地方不能超过字符串
                    string sub = s.substr(start, i);
                    if (isValid(sub)) {
                        s.insert(start + i, 1, '.');
                        backtrack(s, start + i + 1, cnt + 1);
                        s.erase(s.begin() + start + i);
                    }
                }
            }
        }
    }
    
    //判断ip四个段中的一段是否合法
    inline bool isValid(string& s) {
        int len = s.size();
        if (len > 3) return false;  //长度不能超过3
        if (len != 1) {
            if (s[0] == '0')    //不能有前置0
                return false;
            else if (len == 3) {
                int num = stoi(s);
                if (num > 255)  //不能大于255
                    return false;
            }
        }
        return true;
    }
};