/* Leetcode 43.字符串相乘
 * 给定两个以字符串形式表示的非负整数num1和num2,返回num1和num2的乘积,它们的乘积也表示为字符串形式。
 * 说明：
 * num1 和 num2 的长度小于110。
 * num1 和 num2 只包含数字 0-9。
 * num1 和 num2 均不以零开头，除非是数字 0 本身。
 * 不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。
 */
#include <iostream>
#include <vector>
using namespace std;

//自己写的纯手动模仿乘法, 牺牲速度换空间
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string ans, mul;
        for (int j = l2-1; j >= 0; j--) {
            int carry = 0, curj = num2[j] - '0';
            mul = "";   //每次乘法的结果
            for (int i = l1-1; i >= 0; i--) {
                int curi = num1[i] - '0';
                int tmp = (curi * curj) + carry;
                mul.insert(0, 1, (char)(tmp % 10 + '0'));
                carry = tmp / 10;
            }
            if (carry)
                mul.insert(0, 1, (char)(carry + '0'));
            if (ans.empty()) {
                //第一次乘法, 不用错位
                ans += mul;
            } else {
                //错位相加
                //这个idx的初始值画下图就知道了, j离num2末端的距离跟idx离ans末端的距离一样
                biased_sum(ans, mul, ans.size()-(l2-j));
            }
        }
        return ans;
    }
private:
    //错位相加
    void biased_sum(string& ans, string& str, int idx) {
        int j = str.size()-1;
        int carry = 0 ,cur_ans, cur_str, tmp;
        for (int i = idx; i >= 0; i--, j--) {
            cur_ans = ans[i] - '0';
            cur_str = str[j] - '0';
            tmp = cur_ans + cur_str + carry;
            ans[i] = (char)(tmp % 10 + '0');
            carry = tmp >= 10 ? 1 : 0;
        }
        //把剩余的全加上
        while (j >= 0) {
            cur_str = str[j] - '0';
            tmp = cur_str + carry;
            ans.insert(0, 1, (char)(tmp % 10 + '0'));
            carry = tmp >= 10 ? 1 : 0;
            j--;
        }
        if (carry)
            ans.insert(0, 1, '1');
    }
};

//开拓空间, 牺牲一点空间换速度, 具体原理看这里↓
//https://leetcode.com/problems/multiply-strings/discuss/17605/Easiest-JAVA-Solution-with-Graph-Explanation
class Solution2 {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int len1 = num1.size(), len2 = num2.size();
        vector<int> pos(len1 + len2, 0);
        for (int i = len1-1; i >= 0; i--) {
            for (int j = len2 - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = mul + pos[p2];

                pos[p1] += sum / 10;    //把carry加进去
                pos[p2] = sum % 10;
            }
        }
        string ans;
        for (int a : pos) {
            if (!ans.empty() || a)
                ans += (char)(a + '0');
        }
        return ans;
    }
};