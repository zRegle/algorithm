/**
 * Leetcode 297.二叉树的序列化与反序列化
 * 序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
 * 同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
 * 
 * 请设计一个算法来实现二叉树的序列化与反序列化。
 * 这里不限定你的序列 / 反序列化算法执行逻辑，
 * 你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
 */
#include <string>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * bfs
 *   1
 *  / \
 * 2   3
 *    / \
 *   4   5
 * 序列化后: 1 2 3 # # 4 5 # # # #
 * 用 # 代表空节点
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        if (!root) return s;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            if (node) {
                s += to_string(node->val);
                q.push(node->left);
                q.push(node->right);
            } else {
                s += '#';
            }
            /* 节点间用逗号隔开 */
            s += ',';
        }
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string& data) {
        if (data.empty()) return nullptr;
        TreeNode *root;
        /* 首先还原根节点 */
        int pos = data.find(',');
        int val = stoi(data.substr(0, pos));
        root = new TreeNode(val);
        queue<TreeNode*> q;
        q.push(root);
        int i = pos + 1;
        string s;
        /* bfs还原 */
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            /* 还原左孩子 */
            pos = data.find(',', i);
            s = data.substr(i, pos - i);
            if (s != "#") {
                node->left = new TreeNode(stoi(s));
                q.push(node->left);
            }
            /* 还原右孩子 */
            i = pos + 1;
            pos = data.find(',', i);
            s = data.substr(i, pos - i);
            if (s != "#") {
                node->right = new TreeNode(stoi(s));
                q.push(node->right);
            }
            /* 还原兄弟节点 */
            i = pos + 1;
        }
        return root;
    }
};