#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

/**
 * 输入一个质数集合S,设集合T={x | 存在y∈S, 满足x % y == 0}
 * 求出T集合中第K小的数
 * 例如 S ={2, 3}
 * T = {2, 3, 4, 6, 9, 12, 16...}
 * K = 4, 那么输出应该为6
 *
 * 思路:
 * 利用优先级队列, 越小越靠前, 最初队列中只有S中的元素
 * 每次取出队首元素, 挨个乘S中的元素, 然后塞进队列
 * 一直到求出第K个队首
 */

int getNumberK(int* s, int size, int k) {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < size; ++i) q.push(s[i]);
    int num, prev = -1; //num为队首元素, prev为上一个循环的队首元素
    for (int count = 0; count < k; ++count) {
        num = q.top(); q.pop();
        if (num == prev) {
            //重复的元素, 例如第一个队首有2 * 3 = 6, 第二个队首有3 * 2 = 6
            //另外还需注意抵消掉每次循环的count++
            count--;
            continue;
        }
        for (int i = 0; i < size; ++i) {
            q.push(num * s[i]);
        }
        prev = num;
    }
    return prev;
}

int main() {
    int n, k;
    cin>>n>>k;
    auto s = new int[n];
    for (int i = 0; i < n; ++i) {
        cin>>s[i];
    }
    cout<<getNumberK(s, n, k);
    delete[](s);
    s = nullptr;
    return 0;
}

