/* Leetcode 237.删除链表中的节点
 * 请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点。
 * 传入函数的唯一参数为 要被删除的节点 。
 * 提示：
 *  (1)链表至少包含两个节点。
 *  (2)链表中所有节点的值都是唯一的。
 *   (3)给定的节点为非末尾节点并且一定是链表中的一个有效节点。
 *  (4)不要从你的函数中返回任何结果。 
 */
#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/* 将要删除的节点的后继节点的值copy到删除节点上, 然后删除后继节点 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next = node->next;
        ListNode* next_next = next->next;
        node->val = next->val;
        node->next = next_next;
        next->next = NULL;
    }
};