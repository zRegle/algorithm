/* Leectode 106.从中序与后序遍历序列构造二叉树
 * 根据一棵树的中序遍历与后序遍历构造二叉树。
 * 注意: 你可以假设树中没有重复的元素。
 * 例如，给出
 *  中序遍历 inorder = [9,3,15,20,7]
 *  后序遍历 postorder = [9,15,7,20,3]
 * 返回如下的二叉树:
 *      3
 *     / \
 *    9  20
 *      /  \
 *     15   7
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.empty() || inorder.empty()) return nullptr;
        return build(inorder, postorder, postorder.size()-1, 0, inorder.size()-1);
    }

    /**
     * 递归处理函数
     * @param inorder 中序遍历序列
     * @param postorder 后序遍历序列
     * @param rootIdx 后序遍历序列中, 当前根节点的下标
     * @param left 中序遍历序列中当前范围的左边界
     * @param right 中序遍历序列中当前范围的右边界
     * @return
     */
    TreeNode* build(vector<int>& inorder, vector<int>& postorder,int rootIdx, int left, int right) {
        //首先处理边界条件
        if (rootIdx < 0 || left >= inorder.size() || right < 0 || left > right)
            return nullptr;
        if (left == right)
            return new TreeNode(inorder[left]);
        //在中序遍历中寻找根节点下标
        int i = left;
        for (; i <= right; i++) {
            if (inorder[i] == postorder[rootIdx])
                break;
        }
        auto root = new TreeNode(postorder[rootIdx]);
        //后序遍历序列中, 从当前根节点出发, 减去右子树的节点个数后, 就是左子树的根节点
        auto lchild = build(inorder, postorder, rootIdx-(right-i)-1, left, i-1);
        //后序遍历序列中, 根节点前面就是右子树的根节点
        auto rchild = build(inorder, postorder, rootIdx-1, i+1, right);
        root->left = lchild; root->right = rchild;
        return root;
    }
};