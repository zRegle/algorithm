/**
 * Leetcoe 295. 数据流的中位数
 * 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
 * 例如，
 * [2,3,4] 的中位数是 3
 * [2,3] 的中位数是 (2 + 3) / 2 = 2.5
 * 设计一个支持以下两种操作的数据结构：
 *  void addNum(int num) - 从数据流中添加一个整数到数据结构中。
 *  double findMedian() - 返回目前所有元素的中位数。
 * 示例：
 *  addNum(1)
 *  addNum(2)
 *  findMedian() -> 1.5
 *  addNum(3)
 *  findMedian() -> 2
 * 进阶:
 *  如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
 *  如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
 */
#include <queue>
#include <set>
using namespace std;

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        if (maxHeap.empty() && minHeap.empty()) {
            maxHeap.push(num);
            return;
        } else if (maxHeap.size() > minHeap.size()) {
            /* 大顶堆元素比较多, pop出来一个给小顶堆
             * 然后再将元素num插入大顶堆
             * 这样两个堆的元素个数就相等了 */
            maxHeap.push(num);
            int x = maxHeap.top();
            maxHeap.pop();
            minHeap.push(x);
        } else {
            /* 两个堆的元素个数就相等 */
            if (num >= minHeap.top()) {
                /* num应该插入小顶堆中 */
                minHeap.push(num);
                int x = minHeap.top();
                minHeap.pop();
                maxHeap.push(x);
            } else {
                maxHeap.push(num);
            }
        }
    }

    double findMedian() {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) * 0.5;
        else
            return maxHeap.top();
    }

private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<>> minHeap;
};

/* 利用红黑树来解决 */
class Solution {
    multiset<int> data;
    /* 当元素个数为奇数时, l,r都指向中位数
     * 当元素个数为偶数时, l,r中间的两个数 */
    multiset<int>::iterator l, r;
public:
    /** initialize your data structure here. */
    Solution() : l(data.end()), r(data.end()) {}

    void addNum(int num) {
        size_t size = data.size();
        data.insert(num);
        if (size == 0)
            /* num为第一个插入的元素 */
            l = r = data.begin();
        else if (size & 1) {
            /* num插入前元素为奇数
             * 插入后变偶数 */
            if (num < *l)
                /* num插入到了前半部分
                 * 前半部分元素+1, l后移*/
                l--;
            else
                /* num插入到了后半部分
                 * 后半部分元素+1, r前移*/
                r++;
        } else {
            /* num插入前元素为偶数
             * 插入后变奇数 */
            if (*l < num && num < *r) {
                /* num恰好处于l和r之间 */
                l++;
                r--;
            }
            else if (num >= *r)
                /* num插入到了后半部分
                 * 后半部分元素+1, l前移*/
                l++;
            else
                /* num插入到了前半部分
                 * 前半部分元素+1, r后移
                 * 同时更新l
                 *
                 * 为什么要更新l?在multiset中, 插入是稳定的
                 * 即插入相同的元素, 那么一定会插入到最后面. 例如:
                 * 1 4 5 6
                 *   l r  
                 * 插入后, 未调整指针时:
                 * 1 4 4 5 6
                 *   l   r
                 * 如果只是r--了, 那么l的位置就不对了, 所以需要更新l
                 */
                l = --r;
        }
    }

    double findMedian() {
        return (*l + *r) * 0.5;
    }
};