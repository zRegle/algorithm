/**
 * 拼多多7.25笔试
 * 给定一个输入a,b,c,q
 * 最开始集合s中只有元素a
 * 对于s中的每一个元素x
 *   x + b也属于集合s
 *   x * c也属于集合s
 * 判断q是否在集合s中
 * 1 <= q <= 1000000000
 */
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * 超时做法, 通过队列不断生成集合中的元素x
 * 因为q的范围很大, 所以手动模拟很容易超时
 */
bool timeout(int a, int b, int c, int q) {
    queue<int> qq;
    unordered_set<int> s;
    qq.push(a); s.insert(a);
    while (!qq.empty()) {
        int x = qq.front(); qq.pop();
        if (x == q) {
            return true;
        }
        int plus = x + b;
        int mul = x * c;
        if (plus <= q && s.find(plus) == s.end()) {
            s.insert(plus);
            qq.push(plus);
        }
        if (mul <= q && s.find(mul) == s.end()) {
            s.insert(mul);
            qq.push(mul);
        }
    }
    return false;
}

/**
 * 这题是一道数学题, 集合中的所有元素e都可以以下列公式表示:
 *    e = (a + b*x) * c^y
 * 其中x, y是变量, 从0开始计数
 * 只要(a * c^y) % b == q % b
 * 那么b必然出现在集合中
 */
bool judge(int a, int b, int c, int q) {
    int val = a;
    while (val <= q) {
        if (val % b == q % b) {
            return true;
        }
        val *= c;
    }
    return false;
}