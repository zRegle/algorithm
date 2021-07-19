/* Leetcode 143.重排链表
 * 给定一个单链表 L：L0→L1→…→(Ln-1)→Ln ，
 * 将其重新排列后变为： L0→Ln→L1→(Ln-1)→L2→(Ln-2)→…
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * 示例 1:
 *  给定链表 1->2->3->4, 重新排列为 1->4->2->3.
 * 示例 2:
 *  给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
 */
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//第一步: 找到链表中点
//第二部: 从链表中点开始, 反转链表
//第三部: 将后半部分链表插入到前半部分中
class Solution1 {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        auto mid = head, last = head->next;
        //利用快慢指针找到链表中点, O(n/2)
        while (last && last->next) {
            last = last->next->next;
            mid = mid->next;
        }
        if (last && mid->next) {
            //last != NULL时, 节点个数为偶数, mid会指向前半段的最后一个节点
            auto tmp = mid->next;
            //断开前后两个部分
            mid->next = nullptr;
            //mid指向后半部分的头结点
            mid = tmp;
        }
        auto p1 = head;
        //翻转后半部分, O(n/2)
        auto p2 = reverse(mid);
        //拼接两个独立的链表, O(n/2)
        while (p2) {
            auto tmp1 = p1->next;
            auto tmp2 = p2->next;
            p1->next = p2;
            p2->next = tmp1;
            p1 = tmp1;
            p2 = tmp2;
        }
    }
private:
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        auto cur = head;
        ListNode* prev = nullptr;
        while (cur) {
            auto tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }
};

//递归版本
class Solution2 {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        int len = 0;
        auto cur = head;
        while (cur) {
            len++;
            cur = cur->next;
        }
        (void)helper(head, len);
    }
private:
    /**
     * 递归处理内层链表
     * @param start 链表的起始节点
     * @param len 链表长度
     * @return 链表的终止节点
     */
    //Hint: 利用长度这个变量进行递归, 我们就不要每次都遍历链表找到链表的终止节点了
    ListNode* helper(ListNode* start, int len) {
        if (len == 1) return start;
        if (len == 2) return start->next;
        //返回了经过处理的内层链表的终止节点, 即倒数第二个节点
        auto innerEnd = helper(start->next, len-2);
        //倒数第一个节点
        auto end = innerEnd->next;
        auto tmp1 = start->next; //tmp1即内层链表的起始节点
        auto tmp2 = end->next;
        start->next = end;
        end->next = tmp1;
        innerEnd->next = tmp2; //修改内层链表终止节点的next指针, 供上一层递归使用
        //当前链表处理完之后, 内层链表的终止节点就变成了最后一个节点
        return innerEnd;
    }
};

//迭代版本, 利用vector把链表存下来, 剩下的做法跟递归的做法一样
class Solution3 {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        vector<ListNode*> v;
        auto cur = head;
        while (cur) {
            v.push_back(cur);
            cur = cur->next;
        }
        int left = 0, right = v.size()-1;
        //注意, left = right-1或者left = right就要退出循环了
        while (left < right-1) {
            auto start = v[left++], end = v[right--];
            auto tmp1 = start->next, tmp2 = end->next;
            start->next = end;
            end->next = tmp1;
            v[right]->next = tmp2;
        }
    }
};