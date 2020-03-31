/* Leetcdoe 147.对链表进行插入排序
 * 对链表进行插入排序.
 */
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head || !head->next) return head;
        sortedStart = sortedEnd = head;
        auto cur = head->next;
        while (cur) {
            insert(cur);
            cur = sortedEnd->next;
        }
        return sortedStart;
    }
private:
    ListNode* sortedStart, *sortedEnd; //已经排序的区间
    void insert(ListNode* node) {
        //node插入区间的前后两个节点
        auto prev = sortedStart, next = sortedStart;
        while (next != node) {
            if (next->val > node->val) {
                auto tmp = node->next; //将node从原来的位置删除
                sortedEnd->next = tmp;
                if (next == sortedStart) {
                    //如果node要插到表头
                    node->next = sortedStart;
                    sortedStart = node;
                } else {
                    prev->next = node;
                    node->next = next;
                }
                return;
            }
            prev = next;
            next = next->next;
        }
        //如果node要插到表尾, 则需要更新sortedEnd
        sortedEnd = node;
    }
};