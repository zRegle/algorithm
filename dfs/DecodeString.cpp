#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

/**
 * leetcode 394. Decode String
 * 给定一串密码, 文法定义如下
 * code := num[code] | ε
 * num := [1-9]num | ε
 * 数字代表[]里的解密结果的重复次数
 * 例如: 3[a2[c]] -> accaccacc
 *       3[a]2[bc] -> aaabcbc
 *       2[abc]3[cd]ef -> abcabccdcdcdef
 * 要求解密      
 */

class Solution {
public:
    string decodeString(string& s) {
        if (s.length() == 0) return "";
        string res, num;    //结果字符串, 重复的次数(因为重复的次数可能不是一位数)
        stringstream ss;
        for (int i = 0; i < s.length(); ++i) {
            if (isdigit(s[i]))
                num += s[i];
            else if (isalpha(s[i]))
                res += s[i];
            else if (s[i] == '[') {
                //统计遇到的这个'['到对应的']'的字符串长度
                int cnt = 0;
                int j = i;
                for (; j < s.length(); j++) {
                    if (s[j] == '[') cnt++;
                    if (s[j] == ']') cnt--;
                    if (!cnt) break;
                }
                int times = 0;
                if (num.length() > 0) {
                    //转化为int
                    ss<<num;
                    ss>>times;
                    num = "";
                    ss.clear();
                }
                //被"[]"包裹的子字符串
                string subStr = s.substr(i+1, j-i-1);
                //递归处理
                string subRes = decodeString(subStr);
                //重复
                if (!times)
                    res += subRes;
                else {
                    while (times > 0) {
                        res += subRes;
                        times--;
                    }
                }
                //j是']'的位置, 因为for循环会i++, 所以这里赋值成j就好了
                i = j;
            }
        }
        return res;
    }
};

int main() {
    string code = "3[a]2[bc]";
    Solution s;
    cout<<s.decodeString(code)<<endl;
    return 0;
}