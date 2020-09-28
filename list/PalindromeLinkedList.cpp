/* Leetcode 234.回文链表
 * 请判断一个链表是否为回文链表。
 * 你能否用O(n)时间复杂度和O(1)空间复杂度解决此题?
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* 递归的空间O(n)复杂度做法 
 * back先指针递归到链表尾部, 然后在back指针递归返回的同时
 * front指针前进, 并且与back指针比较
 */
class Solution {
public:
    ListNode *front = nullptr;
    bool flag = true; /* 结果 */

    bool isPalindrome(ListNode* head) {
        if (!head) return true;
        front = head;
        check(head);
        return flag;
    }

    void check(ListNode *back) {
        if (back->next) {
            /* back指针先递归到尾部 */
            check(back->next);
            /* back指针递归返回, front指针前进 */
            front = front->next;
        }
        if (flag) {
            /* 只有之前的比较结果为true时才需要继续比较 */
            flag = front->val == back->val;
        }
    }
};

/* 空间复杂度O(1)做法
 * 快慢指针确定链表中点, 同时将前半部分翻转
 * 然后分别比较两部分链表即可
 */
class Solution1 {
    bool isPalindrome(ListNode* head) {
        if (!head) return true;
        ListNode* slow = head, *fast = head;
        /* 用于翻转链表 */
        ListNode* cur = nullptr, *pre = nullptr;
        while (fast && fast->next) {
            cur = slow;
            slow = slow->next;
            fast = fast->next->next;
            cur->next = pre;
            pre = cur;
        }
        if (fast) {
            /* 如果fast不为空, 链表节点数为奇数
             * slow刚好是链表中点, cur为slow的前驱
             */
            slow = slow->next;
        }
        /* 此时cur是前半部分翻转后的head节点
         * slow是后半部分的head节点
         */
        while (cur && slow) {
            if (cur->val != slow->val)
                return false;
            cur = cur->next;
            slow = slow->next;
        }
        return true;
    }
};