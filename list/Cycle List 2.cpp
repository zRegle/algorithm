/* Leetcode 142.环形链表2
 * 给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 */
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//具体证明看这个网址
//https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/linked-list-cycle-ii-kuai-man-zhi-zhen-shuang-zhi-/
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return nullptr;
        //首先利用快慢指针判断有没有环, 有的话返回两个指针相遇的节点
        auto intersect = getIntersect(head);
        if (!intersect) return nullptr;
        //两个指针分别从头结点和相遇的节点出发, 每次走一步, 相遇的地方即为入环点
        auto cur = head;
        while (cur != intersect) {
            cur = cur->next;
            intersect = intersect->next;
        }
        return cur;
    }
private:
    ListNode* getIntersect(ListNode *head) {
        auto slow = head->next, fast = head->next->next;
        while (fast && fast->next) {
            if (fast == slow)
                return fast;
            fast = fast->next->next;
            slow = slow->next;
        }
        return nullptr;
    }
};