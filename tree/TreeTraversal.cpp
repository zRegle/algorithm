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

    //需要判断是从左子树还是右子树返回到根节点
    void postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root, *r = NULL;
        while (!s.empty() || cur) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top();
                //右子树不为空并且右子树没访问过
                if (cur->right && cur->right != r) {
                    cur = cur->right;   //遍历右子树
                } else {
                    s.pop();
                    cout<<cur->val;
                    r = cur;    //记录最近访问过的节点
                    cur = NULL;
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