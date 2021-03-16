/**
 * 剑指offer-18: 树的子结构
 * 输入两棵二叉树A和B, 判断B是不是A的子结构
 * 示例:
 * 二叉树A:     二叉树B:
 *     8         8    
 *    / \       / \
 *   8   7     9   2
 *  / \
 * 9   2
 *    / \
 *   4   7
 * 返回: true
 */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(nullptr), right(nullptr) {
	}
};

/* 分两步:
 * 1.在树A中找到和B根节点一样的节点R
 * 2.判断树A中以R为根节点的子树是不是包含和树B一样的结构
 */

class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (pRoot1 == nullptr || pRoot2 == nullptr) return false;
        bool flag = false;
        if (pRoot1->val == pRoot2->val)
            //当前节点的值相等, 判断pRoot1开始是否包含pRoot2
            flag = isSame(pRoot1, pRoot2);
        if (!flag)
            //pRoot1开始不包含pRoot2, 尝试递归左节点
            flag = HasSubtree(pRoot1->left, pRoot2);
        if (!flag)
            flag = HasSubtree(pRoot1->right, pRoot2);
        return flag;
    }

private:
    /* 判断从r1节点开始, 是否包含r2为根节点的二叉树 */
    bool isSame(TreeNode *r1, TreeNode *r2) {
        //r2已经遍历完了, r1还没遍历完, r1包含r2
        if (r2 == nullptr) return true;
        //r2还没遍历完, r1已经遍历完, r1不包含r2
        if (r1 == nullptr) return false;
        if (r1->val == r2->val)
            return isSame(r1->left, r2->left) && isSame(r1->right, r2->right);
        return false;
    }
};