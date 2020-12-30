/**
 * Leetcode 1654. 到家的最少跳跃次数
 * 有一只跳蚤的家在数轴上的位置 x 处。请你帮助它从位置 0 出发，到达它的家。
 * 跳蚤跳跃的规则如下：
 *  它可以 往前 跳恰好 a 个位置（即往右跳）。
 *  它可以 往后 跳恰好 b 个位置（即往左跳）。
 *  它不能 连续 往后跳 2 次。
 *  它不能跳到任何 forbidden 数组中的位置。
 *  跳蚤可以往前跳 超过 它的家的位置，但是它 不能跳到负整数 的位置。
 * 给你一个整数数组 forbidden ，其中 forbidden[i] 是跳蚤不能跳到的位置，同时给你整数 a， b 和 x ，
 * 请你返回跳蚤到家的最少跳跃次数。如果没有恰好到达 x 的可行方案，请你返回 -1 。
 *  
 * 示例 1：
 *  输入：forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
 *  输出：3
 *  解释：往前跳 3 次（0 -> 3 -> 6 -> 9），跳蚤就到家了。
 * 示例 2：
 *  输入：forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
 *  输出：-1
 * 示例 3：
 *  输入：forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
 *  输出：2
 *  解释：往前跳一次（0 -> 16），然后往回跳一次（16 -> 7），跳蚤就到家了。
 */
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * node——当前位置与下一次是否可以后跳的flag的拼接, 例如:
 * 当前位置为27(二进制为11011), 下一次可以后跳, flag为1
 * 那么node = 110110 | 1 = 110111
 */
#define MAKE_NODE(x, flag) x << 1 | flag
#define GET_FLAG(x) x & 1
#define GET_POS(x) x >> 1

//bfs中需要保存当前位置和在当前位置是否可以后跳的信息
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> visited;
        for (int v : forbidden) {
            //forbidden可以看作是这个位置的两种状态都遍历过了
            visited.insert(MAKE_NODE(v, 1));
            visited.insert(MAKE_NODE(v, 0));
        }
        queue<int> q;
        int node = MAKE_NODE(0, 1);
        q.push(node); visited.insert(node);
        int cnt = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                node = q.front(); q.pop();
                int pos = GET_POS(node), flag = GET_FLAG(node);
                if (pos == x) return cnt;
                int next = pos + a;
                /**
                 * 由于我们可以越过x然后再后跳, 如果不限制搜索范围的话, 将会爆栈
                 * 如果存在到x的路径, 那么搜索范围为[0, M+a+b], M为forbidden数组中的最大值与x进行max后的结果
                 * 具体证明可以看连接:
                 * https://leetcode-cn.com/problems/minimum-jumps-to-reach-home/solution/dao-jia-de-zui-shao-tiao-yue-ci-shu-zui-duan-lu-zh/
                 */
                if (next <= 6000) {
                    node = MAKE_NODE(next, 1);
                    if (visited.find(node) == visited.end()) {
                        visited.insert(node);
                        q.push(node);
                    }
                }
                next = pos - b;
                if (flag == 1 && next >= 0) {
                    //当前位置可以后跳, 且后跳后的位置有效
                    node = MAKE_NODE(next, 0);
                    if (visited.find(node) == visited.end()) {
                        visited.insert(node);
                        q.push(node);
                    }
                }
            }
            cnt++;
        }
        return -1;
    }
};