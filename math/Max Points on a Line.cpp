/**
 * Leetcode 149. 直线上最多的点数
 * 给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点。
 * 求最多有多少个点在同一条直线上。
 *
 * 示例 1：
 *  输入：points = [[1,1],[2,2],[3,3]]
 *  输出：3
 * 示例 2：
 *  输入：points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 *  输出：4
 *
 * 提示：
 *  (1)1 <= points.length <= 300
 *  (2)points[i].length == 2
 *  (3)-10^4 <= xi, yi <= 10^4
 *  (4)points 中的所有点 互不相同
 */
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * 考虑直线方程的表达方式: 点斜式, 即一个点加一个斜率即可唯一的确定一条直线。
 * 我们可以对「点」进行分类然后去求经过某个点的所有直线中，哪条直线上的点最多。
 * 当确定一个点后，平面上的其他点都和这个点可以求出一个斜率，斜率相同的点就意味着在同一条直线上。
 * 我们可以用HashMap去计数，斜率作为 key，然后遍历平面上的其他点，相同的 key 意味着在同一条直线上。
 * 到此, 我们解决了「经过某个点的直线，哪条直线上的点最多」的问题。
 * 接下来只需要换一个点，然后用同样的方法考虑完所有的点即可。
 */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) return n;
        int ans = 0;
        /**
         * key-> 斜率(分子 + @ + 分母, 避免精度丢失)
         * value -> 有多少个点跟固定点的斜率为key
         */
        unordered_map<string, int> map;
        /* 固定一个点, 求其他点跟它的斜率 */
        for (int i = 0; i < n; i++) {
            int cnt = 0; /* 保存经过当前点的直线中, 最多有多少个点共线 */
            for (int j = i + 1; j < n; j++) {
                /* 求分子分母 */
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                /* 约分 */
                int factor = gcd(x, y);
                x /= factor, y /= factor;
                /* 保存斜率 */
                string key = to_string(x) + "@" + to_string(y);
                if (map.find(key) == map.end())
                    map[key] = 0;
                map[key]++;
                cnt = max(cnt, map[key]);
            }
            /* +1代表固定的点 */
            ans = max(ans, cnt + 1);
            map.clear();
        }
        return ans;
    }

private:
    /* 辗转相除法求最大公约数
     * 证明参考链接:
     * https://www.cnblogs.com/zxkwdw/p/11986695.html */
    int gcd(int a, int b) {
        while (b != 0) {
            int tmp = a % b;
            a = b;
            b = tmp;
        }
        return a;
    }
};