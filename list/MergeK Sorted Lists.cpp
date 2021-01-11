#include <iostream>
#include <queue>
using namespace std;

/*
 * leetcode 23. Merge k Sorted Lists
 * 合并k个有序链表, 返回一个有序链表
 * Example:
 * Input:
 * [
 *  1->4->5,
 *  1->3->4,
 *  2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v):val(v),next(NULL) {}
};

/*
 * 思路很简单, 利用一个优先级队列, 一开始将各个链表的头加进来
 * 然后一个一个取出来, 拼接链表就完事了
 */
class Solution {
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        auto cmp = [](const ListNode* n1, const ListNode* n2) -> bool {
            return n1->val > n2->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        for (auto node : lists) {
            if (node)
                q.push(node);
        }
        auto dummy = new ListNode(0);
        auto tail = dummy;
        while (!q.empty()) {
            tail->next = q.top(); q.pop();
            tail = tail->next;
            if (tail->next)
                q.push(tail->next);
        }
        return dummy->next;
    }
};