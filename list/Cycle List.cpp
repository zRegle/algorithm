/* Leetcode 141.环形链表
 * 给定一个链表，判断链表中是否有环。
 */
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        //快慢指针, slow每次只走一步, fast每次走两步
        //如果有环, slow肯定会在某处跟fast相遇
        auto slow = head, fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};