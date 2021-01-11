/* Leetcode 203.移除链表元素
 * 删除链表中等于给定值 val 的所有节点。
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* 迭代法 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy = {-1};
        dummy.next = head;
        auto prev = &dummy, cur = head;
        while (cur) {
            if (cur->val == val)
                /* 去除目标节点 */
                prev->next = cur->next;
            else
                /* 不是目标节点, 更新prev的值 */
                prev = cur;
            cur = cur->next;
        }
        return dummy.next;
    }
};

/* 递归法 */
ListNode* removeElements(ListNode* head, int val) {
    if (!head) return head;
    /* 返回已经处理好的子链表 */
    head->next = removeElements(head->next, val);
    /* 判断是否要去除当前节点 */
    return head->val != val ? head : head->next;
}