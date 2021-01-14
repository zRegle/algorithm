/**
 * Leetcode 1530. 好叶子节点对的数量
 * 给你二叉树的根节点 root 和一个整数 distance 。
 * 如果二叉树中两个 叶 节点之间的 最短路径长度 小于或者等于 distance ，那它们就可以构成一组 好叶子节点对 。
 * 返回树中 好叶子节点对的数量 。
 *
 * 示例:
 *       1
 *     /   \
 *    2     3
 *   / \   / \
 *  4   5 6   7
 *  distance = 3;
 *  输出: 2, 分别为[4,5]和[6, 7]
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 两个叶子节点的距离 = 各自到它们的最低公共祖先的距离和
 * 假设左子树中所有叶子结点集合为LEFT, 右子树中的为RIGHT
 * 那么有:
 * for lleaf in LEFT:
 *  for rleaf in RIGHT:
 *      if dis(lleaf) + dis(rleaf) <= K
 *          good pair count++
 */
class Solution {
public:
    int countPairs(TreeNode* root, int distance) {
        (void)dfs(root, distance);
        return count;
    }

private:
    int count = 0;
    /**
     * dfs后序遍历, 根据左右子树中叶子节点的距离统计good pair数目
     * @param root 当前递归根节点
     * @param distance
     * @return vector<int> —— 所有叶子节点到这个根节点的距离, 从小到大排序
     */
    vector<int> dfs(TreeNode *root, int distance) {
        if (root == nullptr)
            /* 空节点, 返回空vector */
            return {};
        if (root->left == nullptr && root->right == nullptr)
            /* 叶子节点, 返回0 */
            return {0};
        /* 获取叶子节点到左右子树的距离 */
        auto left = dfs(root->left, distance);
        auto right = dfs(root->right, distance);
        /* 归并排序叶子节点到当前节点的距离 */
        int lsize = left.size(), rsize = right.size();
        vector<int> v(lsize + rsize, 0);
        int i = 0, j = 0, idx = 0;
        while (i < lsize && j < rsize) {
            if (left[i] <= right[j])
                /* 到左子树的距离为left[i], 所以要++left[i] */
                v[idx++] = ++left[i++];
            else
                v[idx++] = ++right[j++];
        }
        while (i < lsize) v[idx++] = ++left[i++];
        while (j < rsize) v[idx++] = ++right[j++];
        /* 统计good pair数目 */
        for (i = 0; i < lsize; i++) {
            for (j = 0; j < rsize; j++) {
                if (left[i] + right[j] <= distance)
                    count++;
                else
                    /* 因为left和right都是排好序的
                     * 所以left[i]加(right[j]后面的元素)都肯定大于distance
                     * 此时可以break内层for循环
                     */
                    break;
            }
        }
        return v;
    }
};