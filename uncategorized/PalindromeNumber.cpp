//
// Created by Administrator on 2018/8/4.
//

#include <iostream>
using namespace std;
/**
 * 输入a b, 求出[a, b]内所有回文数字
 */


bool isPalindrome(int num) {
    int div = 1;
    while (div <= num / 10) div *= 10; //确定位数
    while (num > 0) {
        int head = num / div;
        int tail = num % 10;
        if (head != tail) return false;
        //掐头去尾, num%div是去头, 结果在除以10是去尾
        num = (num % div) / 10;
    }
    return true;
}

int main() {
    int a, b;
    cin>>a>>b;
    for (int i = a; i <= b; ++i) {
        if (isPalindrome(i))
            cout<<i<<endl;
    }
    return 0;
}