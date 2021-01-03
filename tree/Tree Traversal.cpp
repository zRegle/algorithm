#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//二叉树三种非递归的遍历方式
class Solution {
public:
    void preoderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (!s.empty() || cur) {
            while (cur) {
                cout<<cur->val;
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            cur = cur->right;
        }
        cout<<endl;
    }

    void inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (!s.empty() || cur) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            cout<<cur->val<<" ";
            cur = cur->right;
        }
        cout<<endl;
    }

    //morris中序遍历, O(1)的空间复杂度, 详细过程看博客
    //https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
    void morris(TreeNode* root) {
        TreeNode* cur = root, *prev = nullptr;
        while (cur) {
            if (!cur->left) {
                //当前没有左子树, 等价于左子树遍历完毕, 直接输出
                cout<<cur->val<<" ";
                //遍历右子树
                cur = cur->right;
            } else {
                prev = cur->left;
                //从左子树出发, 找到前驱节点
                while (prev->right && prev->right != cur)
                    prev = prev->right;
                if (!prev->right) {
                    //前驱的右节点为空, 插一个指针到当前节点
                    //用于标识当前节点的左子树是否遍历完毕
                    prev->right = cur;
                    cur = cur->left;
                } else {
                    //前驱的右节点指向当前节点, 证明左子树遍历完毕
                    //先复原
                    prev->right = nullptr;
                    //输出当前节点的值
                    cout<<cur->val<<" ";
                    //遍历右子树
                    cur = cur->right;   //遍历完最后一个节点时, cur->right为空, 赋值给cur后就会退出循环
                }
            }
        }
    }

    //需要判断是从左子树还是右子树返回到根节点
    void postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root, *recent = nullptr;
        while (!s.empty() || cur) {
            if (cur) { //当前子树还没遍历
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top();
                if (cur->right && cur->right != recent) {
                    //右子树不为空并且右子树没访问过, 表明是从左子树返回的
                    //遍历右子树
                    cur = cur->right;
                } else {
                    //这里有两个情况:
                    //1.没有右子树, 相当于右子树遍历完毕
                    //2.从右子树返回, 表明右子树遍历完毕
                    s.pop();
                    cout<<cur->val<<" "; //输出根节点的值
                    recent = cur;    //记录最近访问过的节点
                    cur = nullptr; //cur置空, 表示当前子树已经遍历完毕
                }
            }
        }
    }
};

int main() {
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    n1->right = n2; n2->left = n3;
    Solution s;
    s.preoderTraversal(n1);
    s.inorderTraversal(n1);
    s.postorderTraversal(n1);
    return 0;
}