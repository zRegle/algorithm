/* Leetcode 92.反转链表2
 * 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
 * 说明:
 * 1 ≤ m ≤ n ≤ 链表长度。
 */
#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int cnt = n - m + 1, idx = 1;
        if (cnt == 1) return head;
        ListNode dummy(-1); dummy.next = head;
        //before是翻转区间的前一个节点
        ListNode* cur = head, *before = &dummy;
        while (idx < m) {
            before = cur;
            cur = cur->next;
            idx++;
        }
        ListNode* first = cur, *last = nullptr, *prev = nullptr;
        //翻转
        for (int i = 1; i <= cnt; i++) {
            if (i == cnt) last = cur;
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        //循环结束后, cur是翻转区间的后一个节点
        first->next = cur;
        before->next = last;
        return dummy.next;
    }
};