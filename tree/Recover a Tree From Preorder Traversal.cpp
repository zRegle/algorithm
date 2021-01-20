#include <string>
#include <stack>
using std::string;
using std::stack;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* leetcode的解法, 迭代版本 */
class Solution {
public:
    TreeNode* recoverFromPreorder(string& s) {
        /* 先序遍历, 栈中有多少个节点, 就代表当前深度是多少 */
        stack<TreeNode*> stk;
        int idx = 0;
        while (idx < s.length()) {
            int level = 0;
            /* 统计当前节点的深度 */
            while (idx < s.length() && s[idx] == '-') {
                level++;
                idx++;
            }
            int val = 0;
            /* 获取当前节点的val */
            while (idx < s.length() && isdigit(s[idx])) {
                val *= 10;
                val += s[idx] - '0';
                idx++;
            }
            auto node = new TreeNode(val);
            if (level == stk.size()) {
                /* 栈中深度恰好等于level, 表明栈顶元素就是父节点 */
                if (!stk.empty())
                    stk.top()->left = node;
            } else {
                /* 一直pop到level等于栈中深度 */
                while (level != stk.size())
                    stk.pop();
                stk.top()->right = node;
            }
            /* node入栈, 等待其子树构建完成 */
            stk.push(node);
        }
        TreeNode *root = nullptr;
        while (!stk.empty()) {
            root = stk.top();
            stk.pop();
        }
        return root;
    }
};

/* 我的解法, 递归版本 */
class MySolution {
public:
    TreeNode* recoverFromPreorder(string& S) {
        int idx = 0;
        return dfs(idx, 0, S);
    }

    /**
     * dfs构建二叉树
     * @param idx 当前应该从s的哪个位置开始遍历
     * @param depth 当前节点的深度
     * @param s 字符串
     * @return 以当前节点为根节点的子树
     */
    TreeNode* dfs(int& idx, int depth, string& s) {
        if (idx == s.length()) return nullptr;
        int val = 0;
        /* 获取当前节点的val */
        while (idx < s.length() && s[idx] != '-') {
            val *= 10;
            val += s[idx] - '0';
            idx++;
        }
        auto root = new TreeNode(val);
        int cnt = 0;
        /**
         * 当前节点的深度为depth, 那么它的孩子节点深度应该为depth + 1
         * 我们要获取depth + 1个'-'后, 紧接着的数字才是当前节点的孩子节点
         */
        depth++; /* 下一层的深度 */
        for (; idx < s.length(); idx++) {
            if (s[idx] != '-') {
                /**
                 * 在还没获取够'-'时就遇到数字, 表明这个数字代表的节点
                 * 是当前节点祖先节点的孩子节点, 需要将idx回退, 供祖先节点调用
                 *
                 * 譬如"1-2--3--4-5--6--7"
                 * 我们在创建好节点4后, 本应获取3个'-',之后的数字才是节点4的孩子节点
                 * 但是我们只获取到了一个'-',之后就是数字5了
                 * 表明数字5是节点4的祖先节点1的孩子节点, 我们需要将idx回退
                 */
                idx -= cnt + 1;
                break;
            }
            cnt++;
            if (cnt == depth) {
                /* 获取足够多的'-', 下个数字就是当前节点的孩子节点 */
                if (!root->left) {
                    root->left = dfs(++idx, depth, s);
                    cnt = 0;
                } else {
                    root->right = dfs(++idx, depth, s);
                    break;
                }
            }
        }
        return root;
    }
};