/* Leetcode 116.填充每个节点的下一个右侧节点指针
 * 给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点
 * 填充它的每个next指针,让这个指针指向其下一个右侧节点.如果找不到下一个右侧节点，则将next指针设置为NULL
 * 初始状态下，所有next指针都被设置为NULL
 * 例如:
 *      1 --> NULL
 *    /   \
 *   2---->3-->NULL
 *  / \   / \
 * 4-->5->6-->7-->NULL
 */

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

//递归版本
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        if (root->left) {
            //不是叶子节点, 连接左右孩子
            root->left->next = root->right;
            if (root->next) {
                //根节点的next指针不为空, 连接根节点的兄弟节点的子节点, 即"堂兄弟"节点
                root->right->next = root->next->left;
            }
        }
        (void)connect(root->left);
        (void)connect(root->right);
        return root;
    }
};

//迭代版本
class Solution2 {
public:
    Node* connect(Node* root) {
        Node* prev = root;
        while (prev) {
            Node* cur = prev;
            while (cur) {
                //连接左右孩子节点
                if (cur->left) {
                    cur->left->next = cur->right;
                    //连接堂兄弟节点
                    if (cur->next) cur->right->next = cur->next->left;
                }
                //处理下一个兄弟节点
                cur = cur->next;
            }
            //这一层处理完毕, 迭代下一层
            prev = prev->left;
        }
        return root;
    }
};