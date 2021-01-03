#include <cstddef>
#include <climits>
using namespace std;

/*
 * leetcode 99. Recover Binary Search Tree
 * 给定一棵二叉搜索树, 其中有两个节点被错误地交换了, 要求还原这棵二叉搜索树
 *
 * 思路:
 * 二叉搜索树的中序遍历出来的串必定是个递增序列, 如果有两个节点被错误地交换, 那么序列中必然有降序的地方
 * 而我们需要找到那两个错误的节点在哪
 * 
 * case1: 两个错误交换的节点在输出序列中是分开的
 *  例如: (其中6和2被交换)
 *       3
 *      / \
 *     6   5
 *        / \
 *       4   2
 *  中序遍历结果: 6 3 4 5 2
 *  有两个降序的地方: [6,3]和[5,2]
 *  我们只需要将第一个降序对中较大的节点和第二个降序对中较小的节点交换, 就能得到有序的序列
 *  
 * case2: 两个错误交换的节点在输出序列中是连续的
 *  例如: (其中2和3被交换)
 *       3
 *      / \
 *     1   4
 *        /
 *       2   
 *  中序遍历结果: 1 3 2 4
 *  降序的地方为[3,2]
 *  我们只需要将这个降序对两个节点交换即可
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    TreeNode* first;
    TreeNode* second;
    TreeNode* prev; //中序遍历前驱节点

    void recoverTree(TreeNode* root) {
        prev = new TreeNode(INT_MIN);
        traverse(root);
        int tmp = first->val;
        first->val = second->val;
        second->val = tmp;
    }

    //中序遍历
    void traverse(TreeNode* root) {
        if (!root) return;
        traverse(root->left);
        //出现降序, 且第一个节点还没找到, 取较大节点
        if (prev->val >= root->val && !first) first = prev;
        //出现降序, 且第一个节点已找到, 取较小节点
        if (prev->val >= root->val && first) second = root;
        prev = root;
        traverse(root->right);
    }
};

//morris中序遍历, 加一点逻辑
class Solution2 {
public:
    void recoverTree(TreeNode* root) {
        if (!root) return;
        TreeNode* first = nullptr, *second = nullptr;
        TreeNode* cur = root;
        TreeNode* precursor = nullptr;  //当前节点有左子树时, 当前节点的前驱节点
        TreeNode* prior = nullptr; //所有的前驱节点
        while (cur) {
            if (cur->left) {
                precursor = cur->left;
                while (precursor->right && precursor->right != cur)
                    //找到当前节点在左子树中的前驱节点
                    precursor = precursor->right;
                if (!precursor->right) {
                    //前驱结点的右指针为空, 加一个指针, 判断是否遍历完当前节点的左子树
                    precursor->right = cur;
                    //开始遍历左子树
                    cur = cur->left;
                    continue;
                } else {
                    //前驱结点的右指针指向当前节点, 左子树遍历完毕, 遍历右子树
                    precursor->right = nullptr;
                }
            }
            //降序对有两对时:
            // first = 第一个降序对中较大的节点, second = 第二个降序对中较小的节点
            //降序对只有一对时:
            // first = 较大的节点, second = 较小的节点
            if (prior && prior->val >= cur->val) {
                if (!first) first = prior;
                second = cur;
            }
            prior = cur;
            cur = cur->right;
        }
        int tmp = first->val;
        first->val = second->val;
        second->val = tmp;
    }
};

int main() {
    auto n1 = new TreeNode(1), n2 = new TreeNode(3), n3 = new TreeNode(2);
    n1->left = n2; n2->right = n3;
    auto s = new Solution();
    s->recoverTree(n1);
    return 0;
}