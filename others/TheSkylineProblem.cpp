/* Leetcode 218.天际线问题
 * 详细问题描述参考链接:
 * https://leetcode-cn.com/problems/the-skyline-problem/
 */
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/* 扫描线法
 * 1.将建筑物拆成两部分, 左边界由左端点和高度的负值表示, 右边界由右端点和高度表示
 * 2.将所有建筑物的两个部分按横坐标从小到大排序, 横坐标相同则比较纵坐标
 * 3.遍历排序后的结果, 遇到左边界就把高度入堆, 右边界就从堆中删除对应的边界
 * 4.入堆和出堆后, 比较堆中的最大高度和之前的最大高度是否一致, 如果不一致就表示这是个转折点, 将其横坐标和当前最大高度填入结果中
 */
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int,int>> h;
        /* multiset允许有重复元素存在, 会对元素排序
         * 并且插入查找删除都可以在logn的时间内完成
         */
        multiset<int> m;
        vector<vector<int>> res;

        //将每一个建筑分成两个部分，例如:[2,9,10]可以转换成[2，-10][9,10]，我们用负值来表示左边界
        for(auto& b : buildings) {
            h.emplace_back(make_pair(b[1], -b[2]));
            h.emplace_back(make_pair(b[1], b[2]));
        }

        /* 这里排序首先会根据pair的first排序, 如果first相同, 就比较second
         * 这样遍历时就会有很大好处, 下面讨论三个edge case
         * 可以参考链接https://www.youtube.com/watch?v=GSBLe8cKu0s&t=736s
         * 从10:17-12:17的例子
         *
         * 1.遇到横坐标相同的左边界时, 优先遍历高度较高的(高度越高, 它的负数就越小)
         *   [[0,2,3],[0,1,2]]
         *   可以看到, 我们要输出的点是[[0,3], [2,0]]
         *   如果我们反过来的话, 输出的点就变成了[[0,2], [2,0]],
         *   而我们知道[0,2]这个左上端点会被[0,3]左上端点覆盖住, 所以是错误的
         *
         * 2.遇到横坐标相同的右边界时, 优先遍历高度较低的
         *   [[3,5,3],[4,5,2]]
         *   可以看到, 我们要输出的端点是[[3,3],[5,0]]
         *   如果我们遍历顺序反过来,那么输出变成了[[3,3],[5,2]]
         *   而我们知道[5,2]这个右上端点会被[5,3]这个右上端点覆盖住, 所以是错误的
         *
         * 3.遇到横坐标相同的左右边界时, 优先遍历左边界(负数比正数小)
         *   [[6,7,2],[7,8,3]]
         *   可以看到, 我们要输出的端点是[[6,2],[7,3],[8,0]]
         *   如果我们遍历顺序反过来,那么输出变成了[[6,2],[7,0],[7,3],[8,0]]
         *   而我们知道[7,0]这个右下端点会被[7,3]这个左上端点覆盖住, 所以是错误的
         *
         * 这就是为什么我们要排序, 并且把左边界的高度设置为负数
         */
        sort(h.begin(),h.end());
        int prev = 0, cur;
        m.insert(0);

        //遍历
        for (auto& i : h) {
            if (i.second < 0)
                //左端点，高度入堆
                m.insert(-i.second);
            else
                //右端点，高度出堆
                m.erase(m.find(i.second));
            //堆里当前的最大高度高度
            cur = *m.rbegin();

            //当前最大高度不等于之前的最大高度, 表示这是一个转折点
            if (cur != prev) {
                //添加坐标
                res.push_back({i.first, cur});
                //更新最大高度
                prev = cur;
            }
        }
        return res;
    }
};

/* 类似于归并排序, 不断将关键点合并 */
class Solution1 {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        if (buildings.empty()) {
            return vector<vector<int>>();
        }
        return merge(0, buildings.size()-1, buildings);
    }

private:
    vector<vector<int>> merge(int start, int end, vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        if (start == end) {
            /* 只剩一个建筑, 分别添加它的左上端点和右下端点 */
            res.emplace_back(vector<int>({buildings[start][0], buildings[start][2]}));
            res.emplace_back(vector<int>({buildings[start][1], 0}));
        } else {
            int mid = (start + end) >> 1;
            auto left = merge(start, mid, buildings);
            auto right = merge(mid+1, end, buildings);

            /* i, j是遍历左右两个关键点集合的下标
             * h1表示当left集合中某个关键点加入到结果res中时, 该关键点的高度, h2同理
             * cur表示合并后天际线的当前高度
             */
            int h1, h2, i, j, cur;
            h1 = h2 = i = j = cur = 0;

            while (i < left.size() && j < right.size()) {
                /* 获取两者横坐标较小值 */
                int x1 = left[i][0], x2 = right[j][0], x;
                if (x1 < x2) {
                    h1 = left[i][1];
                    x = x1;
                    i++;
                } else if (x1 > x2){
                    h2 = right[j][1];
                    x = x2;
                    j++;
                } else {
                    /* 两个横坐标相同, 横坐标随便取, 同时i++, j++ */
                    h1 = left[i][1], h2 = right[j][1];
                    x = x1;
                    i++; j++;
                }
                /* 取两者较大值
                 * 较小值会被较大值覆盖掉, 所以去较大值
                 * 这里画个图举例子比较好理解
                 */
                int maxHeight = max(h1, h2);
                if (maxHeight != cur) {
                    /* 较大值跟之前合并好的天际线高度不一致, 是个转折点 */
                    res.emplace_back(vector<int>({x, maxHeight}));
                    cur = maxHeight;
                }
            }
            while (i < left.size())
                res.push_back(left[i++]);
            while (j < right.size())
                res.push_back(right[j++]);
        }
        return res;
    }
};