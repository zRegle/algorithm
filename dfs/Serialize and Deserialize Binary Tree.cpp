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
 * dfs
 *   1
 *  / \
 * 2   3
 *    / \
 *   4   5
 * 序列化后: 1 2 # # 3 4 # # 5 # #
 * 用 # 代表空节点
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        string s;
        dfsSerialize(root, s);
        return s;
    }

    void dfsSerialize(TreeNode *node, string& s) {
        if (node) {
            s += to_string(node->val);
            /* 节点间用逗号隔开 */
            s += ',';
            dfsSerialize(node->left, s);
            dfsSerialize(node->right, s);
        } else {
            /* 空节点, 然后用逗号隔开 */
            s += "#,";
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        int idx = 0;
        return dfsDeserialize(idx, data);
    }

    /**
     * dfs反序列化
     * @param idx 当前根节点在字符串中的开始位置
     * @param data 序列化好的字符串
     * @return 返回当前根节点
     */
    TreeNode* dfsDeserialize(int& idx, string& data) {
        /* 提取当前根节点 */
        int pos = data.find(',', idx);
        string s = data.substr(idx, pos - idx);
        /* idx移到下一层的根节点开始位置 */
        idx = pos + 1;
        TreeNode *node = nullptr;
        if (s != "#") {
            node = new TreeNode(stoi(s));
            node->left = dfsDeserialize(idx, data);
            node->right = dfsDeserialize(idx, data);
        }
        return node;
    }
};