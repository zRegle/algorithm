/**
 * Leetcode 945. 使数组唯一的最小增量
 * 给定整数数组 A，每次 move 操作将会选择任意 A[i]，并将其递增 1。
 * 返回使 A 中的每个值都是唯一的最少操作次数。
 *
 * 示例 2:
 *  输入：[3,2,1,2,1,7]
 *  输出：6
 *  解释：经过 6 次 move 操作，数组将变为 [3, 4, 1, 2, 5, 7]。
 *      可以看出 5 次或 5 次以下的 move 操作是不能让数组的每个值唯一的。
 * 提示：
 *  (1)0 <= A.length <= 40000
 *  (2)0 <= A[i] < 40000
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 先排序，再依次遍历数组元素，若当前元素小于等于它前一个元素，则将其变为前一个数 +1
 */
class Solution0 {
public:
    int minIncrementForUnique(vector<int>& A) {
        sort(A.begin(), A.end());
        int move = 0;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= A[i-1]) {
                int val = A[i-1] + 1;
                move += val - A[i];
                A[i] = val;
            }
        }
        return move;
    }
};

/**
 * 计数统计: 统计有多少个数需要move
 * 参考下面注释
 */
class Solution1 {
public:
    int minIncrementForUnique(vector<int>& A) {
        /* 统计各个数字出现的次数 */
        vector<int> counter(40001, 0);
        int maxVal = 0; /* 数组中的最大值 */
        for (int x : A) {
            counter[x]++;
            maxVal = max(maxVal, x);
        }
        int move = 0;
        for (int i = 0; i <= maxVal; i++) {
            if (counter[i] > 1) {
                /* i出现不止一次, 有counter[i]-1个数需要move
                 * 将它们都移到后一个格子中 */
                int cnt = counter[i] - 1;
                move += cnt;
                counter[i + 1] += cnt;
            }
        }
        /* maxVal + 1的格子可能有从maxVal中move过来的数字
         * 设maxVal = x, 后续的cnt个数字为[x+1, x+2, ..., x+cnt]
         * 根据求和公式算出结果 */
        int cnt = counter[maxVal + 1] - 1;
        move += (cnt + 1) * cnt / 2;
        return move;
    }
};

/**
 * 这道题换句话说，就是需要把原数组映射到一个地址不冲突的区域，映射后的地址不小于原数组对应的元素
 * 其实和解决 hash 冲突的线性探测法比较相似！
 * 如果地址冲突了，会探测它的下一个位置，如果下一个位置还是冲突，继续向后看，直到第一个不冲突的位置为止
 *
 * 关键点：因为直接线性探测可能会由于冲突导致反复探测耗时太长，因此我们可以考虑探测的过程中进行路径压缩。
 * 怎么路径压缩呢？就是经过某条路径最终探测到一个空位置 x 后，将这条路径上的值都变成空位置所在的下标 x，
 * 那么假如下次探测的点又是这条路径上的点，则可以直接跳转到这次探测到的空位置 x，从 x 开始继续探测
 * 详细的图解可以参考链接:
 * https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/solution/ji-shu-onxian-xing-tan-ce-fa-onpai-xu-onlogn-yi-ya/
 */
class Solution2 {
public:
    int minIncrementForUnique(vector<int>& A) {
        pos.resize(80000, -1); /* -1表示空位 */
        int move = 0;
        for (int x : A) {
            move += findPos(x) - x;
        }
        return move;
    }

private:
    vector<int> pos;
    /* 找到第一个空闲的位置放置x */
    int findPos(int x) {
        int y = pos[x];
        if (y == -1) {
            /* x对应的位置本来就是空的, 直接放置 */
            pos[x] = x;
            return x;
        }
        /* 否则向后查找第一个空位
         * 因为pos[x]中标记了上次寻址得到的空位，因此从pos[x]+1开始寻址就行了 */
        y = findPos(y + 1);
        pos[x] = y; /* 寻址后的新空位要重新赋值给pos[x]，路径压缩就是体现在这里 */
        return y;
    }
};