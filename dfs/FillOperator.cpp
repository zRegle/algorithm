//
// Created by Administrator on 2018/8/2.
//

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/**
 * 给定算式 1 2 3 4 5 6 7 8 9 = n
 * 输入n
 * 每个空位可以选择填+或者-或者不填
 * 求出所有能够使等式成立的方案
 * 例如,输入5
 * 12-34+5-67+89=5
 * 1+23+4-5+6-7-8-9=5
 * 等等
 */

int hasSolution = -1;

//字符串去除所有空格
void trim(string& s) {
    unsigned int index = 0;
    if (!s.empty())
        while ((index = s.find(' ', index)) != string::npos)
            s.erase(index, 1);
}

//计算表达式
bool calc(string& s, int target) {
    int sum = 0, index = 0;
    char lastOperand = '\0';
    trim(s);
    string tmp;
    stringstream ss;
    for (; index < s.length(); ++index) {
        //若是数字或者空位,就表示这个数还没读完,一直读下去
        if (s[index] != '+' && s[index] != '-')
            tmp += s[index];
        else {
            //若遇到操作符
            ss << tmp;
            int num;
            ss >> num;  //转化为数字
            //若上一个操作符是+或者是第一个数字
            if (lastOperand == '+' || lastOperand == '\0') {
                sum += num;
            } else if (lastOperand == '-'){
                sum -= num;
            }
            lastOperand = s[index];
            tmp = "";
            ss.clear();
        }
    }
    //读到末尾了,把最后一个数字算上
    if (!tmp.empty()) {
        int num;
        ss << tmp;
        ss >> num;
        if (lastOperand == '+') {
            sum += num;
        } else if (lastOperand == '-'){
            sum -= num;
        }
    }
    return sum == target;
}

/**
 * dfs构造所有可能的结果
 * @param s 每次递归都要拷贝一份,不能传引用
 * @param index 当前要操作的空位
 * @param target 等式右边的数字
 */
void dfs(string s, int index, int target) {
    if (index == s.length()) {
        if (calc(s, target)) {
            hasSolution = 1;
            cout<<s<<"="<<target<<endl;
        }
    } else {
        //啥都不填
        dfs(s, index + 2, target);

        //填+
        string ss = s;
        ss[index] = '+';
        dfs(ss, index + 2, target);

        //填-
        string sss = s;
        sss[index] = '-';
        dfs(sss, index + 2, target);
    }
}

int main() {
    string s = "1 2 3 4 5 6 7 8 9";
    int target;
    cin>>target;
    dfs(s, 1, target);
    if (hasSolution == -1)
        cout<<"No Solution"<<endl;
}

