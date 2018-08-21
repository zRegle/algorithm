#include <iostream>
using namespace std;

/* leetcode 109. Convert Sorted List to Binary Search Tree
 * 给定一个单向链表, 其中存储的值是二叉搜索树的中序遍历的结果, 要求还原这棵二叉树, 并且是平衡二叉树
 * 
 * 思路:
 * 每次挑链表的中间值作为根节点, 然后分左右子树分别递归
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) return nullptr;
        return sortedListToBST(head, nullptr);
    }

    TreeNode* sortedListToBST(ListNode* head, ListNode* tail) {
        if (head == tail) return nullptr;
        auto slow = head, fast = head;
        //fast的速度是slow的两倍, 当fast走到终点时, slow刚好在中点
        while (fast != tail && fast->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }
        int val = slow->val;
        auto root = new TreeNode(val);
        root->left = sortedListToBST(head, slow);
        root->right = sortedListToBST(slow->next, tail);
        return root;
    }
};