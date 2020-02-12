/* Leetcode 206.反转链表
 * 反转一个单链表。
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){}
};

//迭代版本
class Solution1 {
public:
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        auto cur = head;
        ListNode* prev = nullptr;
        while (cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

//递归版本
class Solution2 {
public:
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        auto last = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};