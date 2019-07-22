/* Leetcode 25
 * 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度。
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 * 示例 :
 * 给定这个链表：1->2->3->4->5
 * 当 k = 2 时，应当返回: 2->1->4->3->5
 * 当 k = 3 时，应当返回: 3->2->1->4->5
 */

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