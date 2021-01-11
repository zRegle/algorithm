/* Leetcode 82.删除排序链表中的重复元素2
 * 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
 * 示例 1:
 * 输入: 1->2->3->3->4->4->5
 * 输出: 1->2->5
 */
#include <cstddef>
#include <climits>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !(head->next)) return head;
        ListNode dummy(INT_MIN); dummy.next = head;
        ListNode* cur = head, *prev = &dummy;
        while (cur) {
            //遇到重复时, prev指向第一个重复项的前面, cur指向最后一个重复项
            while (cur->next && cur->next->val == cur->val)
                cur = cur->next;
            if (prev->next != cur)
                //如果真的有重复项, prev和cur不相邻, 直接删除重复元素
                prev->next = cur->next;
            else
                //没有重复项, 往下一个节点走
                prev = cur;
            cur = cur->next;
        }
        return dummy.next;
    }
};