//
// Created by Administrator on 2018/8/4.
//
#include <iostream>
using namespace std;
/**
 * 找最大值
 * f(x)是一个凸函数, 对其均匀采样N份得到序列f(i), 1 <= i <= N
 * 接下来轮询m次,每次输入a, b
 * 求出f(i) - a * i - b的最大值
 * 输入n, m代表采样个数, 轮询次数
 * 输入n个样本点数据
 * 接下来每行输入a, b
 * 例如输入:
 * 3 2
 * 1 3 2
 * 1 3
 * 2 4
 * 输出:
 * -2
 * -5
 */

//三分法,逐步逼近凸点, 按照程序画图比较好理解
int findPoint(int* p, int left, int right, int a) {
    if (left == right - 1)
        return p[left] - a * left > p[right] - a * right ? left : right;
    int mid = (left + right) / 2;
    int mmid = (mid + right) / 2;
    if (p[mid] - a * mid > p[mmid] - a * mmid)
        return findPoint(p, left, mmid, a);
    else
        return findPoint(p, mid, right, a);
}


int main() {
    int n, m;
    int* p = new int[n];
    int a, b, index;
    for (int i = 0; i < m; ++i) {
        cin>>a>>b;
        index = findPoint(p, 0, n - 1, a);
        cout<<p[index] - a * index - b<<endl;
    }
    delete[](p);
    return 0;
}