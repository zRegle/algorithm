/**
 * Leetcode 1104. 二叉树寻路
 * 在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 逐行 依次按 “之” 字形进行标记。
 * 如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；
 * 而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记。
 *            1
 *       /         \
 *      2           3
 *    /   \       /   \
 *   4     5     6     7
 *  / \   / \   / \   / \
 * 15 14 13 12 11 10 9   8
 *         ......
 * 给你树上某一个节点的标号label，请你返回从根节点到该标号为label 节点的路径，
 * 该路径是由途经的节点标号所组成的。
 *
 * 示例 1：
 *  输入：label = 14
 *  输出：[1,3,4,14]
 * 示例 2：
 *  输入：label = 26
 *  输出：[1,2,6,10,26]
 */
#include <vector>
#include <ctgmath>
using namespace std;

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        /* 算出label在第几层 */
        int level = (int)log2(label);
        vector<int> path(level+1);
        path[level] = label;
        int cur = label;
        while (level) {
            /* 在正常满二叉树的情况下
             * 求当前节点的父节点 */
            int parent = cur >> 1;
            /* 正常满二叉树的情况下
             * 父节点所在层的起始节点和结尾节点 */
            int s = 1 << (level-1), e = (1 << level) - 1;
            /* parent翻转前后的标记之和为s + e - 1
             * 因此翻转后的标记为s + e - parent
             * 例如第4层: 8 9 10 11 12 13 14 15, 以13为例
             * 翻转后处于原来10的位置, 10 = 8 + 15 - 13*/
            cur = s + e - parent;
            /* 填充父节点 */
            path[--level] = cur;
        }
        return path;
    }
};