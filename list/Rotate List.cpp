/**
 * Leetcode 61. 旋转链表
 * 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
 *
 * 示例1:
 * 1->2->3->4->5, k=2
 * k=1, 5->1->2->3->4
 * k=2, 4->5->1->2->3
 *
 * 示例2:
 * 1->2->3, k=4
 * k=1, 3->1->2
 * k=2, 2->3->1
 * k=3, 1->2->3
 * k=4, 3->1->2
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 思路一:
 * 将最后k个节点从链表中断开, 最后一个节点指向第一个节点
 * 倒数第k个节点作为新的头节点 */
class Solution {
public:
    ListNode* rotateRight(ListNode *head, int k) {
        if (!head) return nullptr;
        int len = 0;
        auto cur = head;
        /* 统计链表长度 */
        while (cur) {
            len++;
            cur = cur->next;
        }
        /* k对len取模 */
        k %= len;
        if (k == 0)
            /* 取模后为0, 链表原封不动 */
            return head;
        /* 下面代码使cur指向倒数第k个节点, tail指向最后一个节点 */
        auto tail = head;
        for (int i = 0; i < k-1; i++)
            tail = tail->next;
        cur = head;
        /* 以上代码结束后, cur指向第一个节点, tail指向第k个节点 */
        ListNode *prev = nullptr;
        while (tail->next != nullptr) {
            prev = cur;
            cur = cur->next;
            tail = tail->next;
        }
        /* 断开prev指向cur的next指针 */
        prev->next = nullptr;
        /* 最后一个节点的next指向原来的第一个节点 */
        tail->next = head;
        /* 返回cur指针 */
        return cur;
    }
};

/* 思路二:
 * 首先翻转整个链表, 然后前k个节点翻转, 剩下len-k个节点翻转, 最后拼接起来 */
class Solution1 {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;
        int len = 0;
        auto cur = head;
        /* 统计链表长度 */
        while (cur) {
            len++;
            cur = cur->next;
        }
        /* k对len取模 */
        k %= len;
        if (k == 0)
            /* 取模后为0, 链表原封不动 */
            return head;
        /* 翻转整个链表 */
        head = reverse(head, nullptr);
        auto node = head;
        while (k--) {
            node = node->next;
        }
        auto tmp = head;
        /* 翻转前k个节点 */
        head = reverse(head, node);
        /* 翻转剩下len-k个节点 */
        auto next = reverse(node, nullptr);
        /* 两段连接起来 */
        tmp->next = next;
        return head;
    }

    /* 翻转[head, tail)区间的节点 */
    ListNode* reverse(ListNode *head, ListNode *tail) {
        if (head->next == tail) {
            /* 区间只有head一个节点, 断开它的next指针 */
            head->next = nullptr;
            return head;
        }
        ListNode *cur = head, *prev = nullptr;
        while (cur != tail) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};