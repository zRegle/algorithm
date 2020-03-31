/* Leetcode 160.相交链表
 * 编写一个程序, 找到两个单链表相交的起始节点.
 * 注意：
 *  如果两个链表没有交点，返回null.
 *  在返回结果后, 两个链表仍须保持原有的结构.
 *  可假定整个链表结构中没有循环.
 *  程序尽量满足O(n)时间复杂度, 且仅用O(1)内存.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//假设两个链表有相交点
//A链表相交点前长度为x, B链表相交点前长度为y, 相交点后长度为z
//那么必定有x+z+y = y+z+x, 令p1和p2两个指针分别走这两条路线, 当p1 = p2时就是交叉点
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto p1 = headA, p2 = headB;
        while (p1 != p2) {
            p1 = p1 ? p1->next : headB;
            p2 = p2 ? p2->next : headA;
        }
        //这里有两种情况:
        //1.p1 = p2 = 交叉点, 直接返回
        //2.p1 = p2 = null, p1和p2同时到达链表尾部, 没有相交点
        return p1;
    }
};