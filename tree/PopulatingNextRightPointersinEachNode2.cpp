/* leetcode 117. Populating Next Right Pointers in Each Node II
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
        Node* head = nullptr; //root中第一个不为空的子节点
        if (root->left)
            head = root->left;
        if (root->right) {
            if (head) {
                head->next = root->right;
                head = root->right;
            } else {
                head = root->right;
            }
        }
        if (head) {
            //从左往右遍历, 找到第一个不为空的子节点, 连接head
            Node* cur = root->next;
            while (cur) {
                if (cur->left) {
                    head->next = cur->left;
                    break;
                } else if (cur->right) {
                    head->next = cur->right;
                    break;
                }
                cur = cur->next;
            }
        }
        //需要先递归右子树, 把右子树的内的兄弟节点连接好
        //这样子在递归左子树时才能正确地找到右子树中的next指针
        (void)connect(root->right);
        (void)connect(root->left);
        return root;
    }
};

//迭代版本
class Solution2 {
public:
    Node* connect(Node* root) {
        Node *head = nullptr; //root的下一层的头结点
        Node* prev = nullptr; //用于连接root下一层的节点, 可以理解为链表中的prev
        Node *cur = root;
        while (cur) {
            while (cur) {   //处理当前层
                //循环干了两件事
                //1.从左往右扫, 找到第一个节点, 它的左右子节点至少有一个不为空, 把第一个不为空的子节点设置为head
                //2.从左往右填充这一层节点的子节点的next指针
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
                cur = cur->next; //处理下一个兄弟节点
            }
            cur = head; //迭代下一层
            prev = head = nullptr;
        }
        return root;
    }
};