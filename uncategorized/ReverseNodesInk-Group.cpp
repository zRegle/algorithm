struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        auto cur = head;
        int count = 0;
        while (count < k && cur != NULL) {
            cur = cur->next;
            count++;
        }
        if (count < k) return head;
        auto next_head = reverseKGroup(cur, k); //递归处理剩下的节点
        auto tail = head;
        //将节点一个一个移到链表头
        while (count > 0) {
            auto next_next = tail->next->next;
            tail->next->next = head;
            head = tail->next;
            tail->next = next_next;
            count--;
        }
        tail->next = next_head;
        return head;
    }
};