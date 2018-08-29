import java.util.List;
import java.util.ArrayList;
import java.util.LinkList;
/**
 * leetcode 103. Binary Tree Zigzag Level Order Traversal
 * 给定一棵二叉树, 要求Z字层次遍历, 返回一个数组, 每个元素是某一层的遍历结果
 *
 * 例如:
 *   3
 *  / \
 * 9  20
 *   / \
 *  15  7
 *
 * 返回:
 * [
 *  [3],
 *  [20,9],
 *  [15,7]
 * ]
 * 
 * 思路: dfs
 * 利用level变量从结果集中获取对应层的遍历结果链表
 * 利用链表, 加到尾部加到头部, 来分别代表顺序和倒序
 * 
 * 另外一种bfs的解法请去看bfs文件夹
 */
class Solution {
    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList();
        travel(res, 0, root);
        return res;
    }
    private void travel(List<List<Integer>> res, int level, TreeNode cur) {
        if (cur == null) return;
        //层数不够了
        if (res.size() <= level) {
            res.add(new LinkList<Integer>());
        }
        List<Integer> list = res.get(level);
        if ((i>>1)&1 == 0) {    //等价于i%2==0
            list.add(cur.val);  //加到链表尾部
        } else {
         list.add(0, cur.val); //加到链表头部
        }
        travel(res, level + 1, cur.left);
        travel(res, level + 1, cur.right);
    }
}

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}
