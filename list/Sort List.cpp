/* Leetcdoe 148.链表排序
 * 在O(nlogn)时间复杂度和常数级空间复杂度下, 对链表进行排序.
 */
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//归并排序
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        auto cur = head;
        while (cur = cur->next, cur->next);
        auto p = sort(head, cur);
        return p.first;
    }
private:
    pair<ListNode*, ListNode*> sort(ListNode* left, ListNode* right) {
        if (left != right) {
            //快慢指针找中点
            auto slow = left, fast = left->next;
            while (fast != right) {
                if (fast->next == right) {
                    //节点个数为奇数, slow要再前进一步
                    slow = slow->next;
                    break;
                }
                slow = slow->next;
                fast = fast->next->next;
            }
            auto lp = sort(left, slow);
            //注意这里第一个参数不要填slow->next
            //因为进过上一条语句的递归, slow不一定指向中点了
            //lp->second是前面已经排好序区间的终点, 它的next就是待排序区间的起点了
            auto rp = sort(lp.second->next, right);
            auto mp = merge(lp.first, lp.second, rp.first, rp.second);
            return mp;
        } else {
            pair<ListNode*, ListNode*> p(left, left);
            return p;
        }
    }

    /**
     * 合并两个区间
     * @param l1 第一个区间的起点
     * @param r1 第一个区间的终点
     * @param l2 第二个区间的起点
     * @param r2 第二个区间的终点
     * @return 合并后区间的起点和终点
     */
    pair<ListNode*, ListNode*> merge(ListNode* l1, ListNode* r1, ListNode* l2, ListNode* r2) {
        auto p1 = l1, p2 = l2;
        auto tmp = r2->next; //保存合并后区间的下一个节点
        r1->next = nullptr; r2->next = nullptr; //先断开两个区间
        ListNode* head = nullptr, *tail = nullptr;
        while (p1 && p2) {
            ListNode* node;
            if (p1->val < p2->val) {
                node = p1;
                p1 = p1->next;
            } else {
                node = p2;
                p2 = p2->next;
            }
            if (!head) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            node->next = nullptr; //置空插入的节点
        }
        //把两个区间剩余的节点都加进来
        while (p1) {
            tail->next = p1;
            tail = p1;
            p1 = p1->next;
        }
        while (p2) {
            tail->next = p2;
            tail = p2;
            p2 = p2->next;
        }
        tail->next = tmp; //保证链表不断裂
        pair<ListNode*, ListNode*> p(head, tail);
        return p;
    }
};