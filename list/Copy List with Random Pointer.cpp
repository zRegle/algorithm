/* Leetcode 138.复制带随机指针的链表
 * 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。要求返回这个链表的深拷贝。
 */
#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

//O(n)空间复杂度的做法
class Solution1 {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        auto newHead= new Node(head->val);
        map[head] = newHead;
        auto p1 = head, p2 = newHead;
        while (p1) {
            p2->next = getClonedNode(p1->next);
            p2->random = getClonedNode(p2->random);
            p1 = p1->next;
            p2 = p2->next;
        }
        return newHead;
    }
private:
    unordered_map<Node*, Node*> map;//旧节点->新节点
    Node* getClonedNode(Node* node) {
        if (!node) return nullptr;
        auto it = map.find(node);
        if (it != map.end())
            return it->second;
        else {
            auto newNode = new Node(node->val);
            map[node] = newNode;
            return newNode;
        }
    }
};

//O(1)空间复杂度的做法
//主要思路是将新老节点放在一起, 例如:
//原链表: A->B->C
//中间链表: A->A'->B->B'->C->C'
//然后遍历中间链表将random指针连起来
//最后拆分中间链表, 同时连接新链表的next指针
class Solution2 {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        auto oldCur = head;
        //产生中间链表, 原节点的next指向拷贝的新节点, 新节点的next指向原节点的下一个节点
        while (oldCur) {
            auto node = new Node(oldCur->val);
            auto oldNext = oldCur->next;
            oldCur->next = node;
            node->next = oldNext;
            oldCur = oldNext;
        }
        oldCur = head; //原链表的头指针
        auto newHead = head->next;
        //遍历中间链表, 连接新链表的random指针
        //两个注意事项:
        //1.这里我们还不能同时拆开链表, 因为要拆开势必要修改oldCur->next
        //  这样如果后面节点的random指向前面的节点, 我们就无法通过random指向的原节点的next指针找到拷贝节点了
        //2.这里同样不能连接新链表的next指针, 因为:
        //   (1)要连接新链表的next指针就要修改newNode->next, newNode不再指向原节点的下一个节点
        //   (2)在第一点中我们不能修改oldCur->next,
        //  两点结合, 强行连接新链表的next指针就会导致原链表断链
        while (oldCur) {
            auto newNode = oldCur->next;
            if (oldCur->random)
                newNode->random = oldCur->random->next;
            oldCur = newNode->next;
        }
        oldCur = head;
        //重新遍历中间链表, 将原链表和新链表拆开, 同时连接新链表的next指针
        while (oldCur) {
            auto newNode = oldCur->next;
            oldCur->next = oldCur->next->next;
            if (oldCur->next)
                newNode->next = newNode->next->next;
            oldCur = oldCur->next;
        }
        return newHead;
    }
};