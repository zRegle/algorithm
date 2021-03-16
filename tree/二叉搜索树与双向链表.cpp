/**
 * 剑指 Offer 36. 二叉搜索树与双向链表
 * 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。
 * 要求不能创建任何新的节点，只能调整树中节点指针的指向。
 *
 * 为了让您更好地理解问题，以下面的二叉搜索树为例：
 *     4
 *    / \
 *   2   5
 *  / \
 * 1  3
 *
 * 我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。
 * 对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
 * 下面展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。
 * head
 *  1 <-> 2 <-> 3 <-> 4 <-> 5
 *  |_______________________|
 *
 * 特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，
 * 树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。
 */
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) return nullptr;
        dfs(root);
        /* 填充头尾节点的双向指针 */
        head->left = pre;
        pre->right = head;
        return head;
    }

private:
    /**
     * head: 二叉树中最左节点
     * pre: root的前驱节点
     */
    Node *head = nullptr, *pre = nullptr;
    void dfs(Node *root) {
        if (root == nullptr) return;
        dfs(root->left);
        if (pre != nullptr)
            /* 前驱不为空, 前驱的指向当前节点 */
            pre->right = root;
        else
            /* root是二叉树的最左节点 */
            head = root;
        /* 当前节点指向前驱节点 */
        root->left = pre;
        /* 当前节点是右子树的前驱节点 */
        pre = root;
        dfs(root->right);
    }
};