#include <iostream>
#include <climits>
using namespace std;

/*
 * leetcode 117. Populating Next Right Pointers in Each Node II
 * 给定一棵二叉树, 每个节点多了一个指针next, 指向最靠近它右边的节点, 初始next都为NULL
 * 要求正确填写这棵树所有节点的next指针
 * 例如:
 *       1-->NULL
 *      / \
 *     2-->3-->NULL
 *    / \   \
 *   4-->5-->7-->NULL
 *  /     \
 * 6------->8-->NULL
 */

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode* head = nullptr;   //下一层的头结点
        TreeLinkNode* prev = nullptr;
        TreeLinkNode* cur = root;
        while (cur) {   //迭代下一层
            while (cur) {   //处理当前层
                //循环干了几件事
                //1.从左往右扫, 找到第一个节点, 它的左右子树至少有一个不为空, 把它设置为head
                //2.连接当前节点的子节点的next指针
                if (cur->left) {
                    if (prev) prev->next = cur->left;
                    else head = cur->left;
                    prev = cur->left;
                }
                if (cur->right) {
                    if (prev) prev->next = cur->right;
                    else head = cur->right;
                    prev = cur->right;
                }
                cur = cur->next;
            }
            cur = head;
            prev = head = nullptr;
        }
    }
};