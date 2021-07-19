/**
 * Leetcode 24. 两两交换链表中的节点
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * 
 * 示例 1：
 *  输入：head = [1,2,3,4]
 *  输出：[2,1,4,3]
 * 示例 2：
 *  输入：head = []
 *  输出：[]
 * 示例 3：
 *  输入：head = [1]
 *  输出：[1]
 *  
 * 提示：
 *  (1)链表中节点的数目在范围 [0, 100] 内
 *  (2)0 <= Node.val <= 100
 */
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution{
    public:
        ListNode* swapPairs(ListNode* head) {
            if(head == nullptr || head->next == nullptr) return head;
            ListNode dummy(-1); dummy.next = head;
            auto cur = head, prev = &dummy;
            while(cur != nullptr && cur->next != nullptr){
                auto next_cur = cur->next->next;
                /* 翻转当前的两个节点 */
                cur->next->next = cur;
                /* 连接之前的节点 */
                prev->next = cur->next;
                cur->next = next_cur;
                /* 继续处理下一对节点 */
                prev = cur;
                cur = next_cur;
            }
            return dummy.next;
        }
};