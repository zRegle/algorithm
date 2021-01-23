/**
 * Leetcode 430. 扁平化多级双向链表
 * 多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，
 * 可能指向单独的双向链表。这些子列表也可能会有一个或多个自己的子项，
 * 依此类推，生成多级数据结构，如下面的示例所示。
 * 
 * 输入:
 *  1<--->2<--->3<--->4<--->5<--->6-->NULL
 *        |
 *        7<--->8<--->9<--->10-->NULL
 *              |
 *             11<-->12-->NULL
 * 给你位于列表第一级的头节点，请你扁平化列表，使所有结点出现在单级双链表中。
 * 输出:
 * 1<-->2<-->7<-->8<-->11<-->12<-->9<-->10<-->3<-->4<-->5<-->6-->NULL
 */

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int val) {
        this->val = val;
        prev = next = child = nullptr;
    }
};

class Solution {
public:
    Node* flattern(Node *head) {
        Node dummy(-1);
        (void)flatten(head, &dummy);
        head->prev = nullptr;
        return head;
    }

private:
    /* 返回flatten后的链表尾部 */
    Node* flatten(Node *cur, Node *prev) {
        if (cur == nullptr) return prev;
        cur->prev = prev;
        prev->next = cur;

        Node *next = cur->next; /* cur->next在递归过程中会改变, 先保存下来 */
        Node *tail = flatten(cur->child, cur); /* 递归flatten */
        cur->child = nullptr; /* 置空child指针 */

        return flatten(next, tail);
    }
};


/* my ugly solution, pass anyway */
class MySolution {
public:
    Node* flatten(Node* head) {
        (void)dfs(head);
        return head;
    }

private:
    /* 返回flatten后的尾部节点 */
    Node* dfs(Node *head) {
        Node *cur = head, *last, *next, *child;
        while (cur) {
            next = cur->next;
            if ((child = cur->child)) {
                /* 如果有child链表 */
                cur->child = nullptr; /* 首先置空child指针 */
                cur->next = child; /* next指针变成child链表的头结点 */
                child->prev = cur; /* 设置child链表头结点的prev指针 */
                last = dfs(child); /* 递归, 返回flatten child链表后的尾部 */
                last->next = next; /* 设置尾部的next指针 */
                if (next) next->prev = last; /* 如果next不为空, 设置next的prev指针 */
                cur = last; /* 更新cur到last */
            }
            if (!cur->next)
                /* 没有next节点, 这就是flatten后的尾部 */
                return cur;
            cur->next->prev = cur;
            cur = cur->next;
        }
        return cur;
    }
};