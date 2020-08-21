/* 222. 完全二叉树的节点个数
 * 给出一个完全二叉树，求出该树的节点个数。
 * 完全二叉树的定义如下：
 * 在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，
 * 并且最下面一层的节点都集中在该层最左边的若干位置。
 * 若最底层为第h 层，则该层包含1-2^h个节点。
 */
#include <cstddef>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* 两种方法本质上都是二分法 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return NULL;
        int left = height(root->left);
        int right = height(root->right);
        if (left == right) {
            /* 节点已经填充到右子树, 那么左子树必定是满的
             * 左子树节点数为 2^left-1, 加上根节点就是2^left
             * 最后递归加上右子树的节点即可
             */
            return countNodes(root->right) + (1 << left);
        } else {
            /* 最后一层不满, 倒数第二层已经满了, 因此可以知道右子树也是满的
             * 同理, 根节点 + 右子树节点数 = 2^right
             * 最后递归加上左子树节点即可
             */
            return countNodes(root->left) + (1 << right);
        }
    }

private:
    /* 根据完全二叉树的特点, 不用递归统计树高, 直接迭代即可 */
    int height(TreeNode* root) {
        int cnt = 0;
        while (root) {
            cnt++;
            root = root->left;
        }
        return cnt;
    }
};

/* 利用二分搜索确定最后一层有多少个节点 */
class Solution2 {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int d = height(root);
        if (d == 0) return 1; /* 只有一个节点 */

        /* 最底层最多有2^d个节点
         * 标号从0 -> 2^d-1
         */
        int left = 1, right = (1 << d) - 1;
        int pivot;
        while (left <= right) {
            pivot = left + ((right - left) << 1);
            if (exist(pivot, d, root))
                /* 最底层的pivot节点存在, 那么证明最底层至少有pivot个节点 */
                left = pivot + 1;
            else
                /* 最底层的pivot节点不存在, 需要继续二分搜索确定 */
                right = pivot - 1;
        }
        /* 前d-1层有2^(d-1)个节点, 最后一层有left个节点 */
        return (1 << d - 1) + left;
    }

private:
    int height(TreeNode* root) {
        int cnt = 0;
        while (root) {
            cnt++;
            root = root->left;
        }
        return cnt;
    }

    bool exist(int idx, int d, TreeNode* node) {
        int left = 0, right = (1 << d) - 1;
        int pivot;
        /* 根节点根据pivot的位置不断调整位置沉到最底层的idx节点
         * 然后判断这个节点是否存在
         */
        for (int i = 0; i < d; i++) {
            pivot = left + ((right - left) << 1);
            if (idx <= pivot) {
                /* idx在pivot左边, 节点切换到左子树
                 * 右边界随之更新
                 */
                node = node->left;
                right = pivot;
            } else {
                node = node->right;
                left = pivot + 1;
            }
        }
        return node != NULL;
    }
};