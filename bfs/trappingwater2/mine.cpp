#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/**
 * leetcode 407 Trapping Rain Water 2
 * 给定一个二维数组, 表示格子高度, 问这个容器最多能容纳多少雨水
 * 例如:
 * [
 *  [1,4,3,1,3,2],
 *  [3,2,1,3,2,4],
 *  [2,3,3,2,3,1]  
 * ]
 * 输出: 4
 * 解释: 坐标(1,1)可以容纳一个水单位, (1,2)可以容纳两个水单位, (1,4)可以容纳1个水单位, 总共4个水单位
 *
 * 思路:
 * 不断套用"木桶原理", 同时更新最短的那块木板的高度, 具体看下面
 */

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int row = heightMap.size();
        if (!row) return 0;
        int column = heightMap[0].size();
        if (!column) return 0;
        //一个格子有四个木板作为边界, 可能之前用某个木板计算过容纳多少水了, 所以需要标记数组
        vector<vector<bool>> visit(row, vector<bool>(column, false));   
        //priority_queue默认是最大堆, 提供一个比较函数, 实质上就是重载<
        auto cmp = [&heightMap](const pair<int, int>& p1, const pair<int, int>& p2) -> bool {
            return heightMap[p1.first][p1.second] > heightMap[p2.first][p2.second];
        };
        //decltype是只想要表达式的类型, 但是不想计算这个表达式
        //q(cmp) 表示使用这个比较器来比较
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);   //边界队列
        //把矩阵的左右两边入队列
        for (int i = 0; i < row; i++) {
            visit[i][0] = visit[i][column-1] = true;
            q.push(make_pair(i, 0));
            q.push(make_pair(i, column-1));
        }
        //把矩阵的上下两边入队列
        for (int j = 0; j < column; j++) {
            visit[0][j] = visit[row-1][j] = true;
            q.push(make_pair(0, j));
            q.push(make_pair(row-1 , j));
        }
        //以上两个循环就构成了最初的容器

        //方向数组
        vector<pair<int ,int>> dirs;
        dirs.emplace_back(make_pair(1, 0)); dirs.emplace_back(make_pair(-1, 0));
        dirs.emplace_back(make_pair(0, 1)); dirs.emplace_back(make_pair(0, -1));

        int water = 0;
        int _max = INT_MIN; //边界的最短木板高度
        //从最初的容器逐步收缩, 最终收缩到一个点
        while (!q.empty()) {
            auto c = q.top(); q.pop();  //最短的那块木板
            int x = c.first, y = c.second;
            //因为我们是从外围逐渐收缩, 所以如果遇到了更高的板子, 我们应该更新变量, 作为内圈的最短板子
            _max = max(_max, heightMap[x][y]);  

            /* 计算以这块木板为边的格子能容纳多少水, 
             * 因为我们拿出来的木板是最短, 所以如果这块木板高于它的邻居, 肯定可以容纳它邻居的水
             * 例如:
             * [1,4,3,1,3,2]
             * [3,2,1,3,2,4]
             * [2,3,3,2,3,1]
             * 以(1, 1)为例, 它高度是2
             * 它的邻居(1, 2)高度是1, 那么肯定可以容纳一个单位的水
             * 虽然(1, 2)的其它边界我们不清楚在哪, 但是它的其他边界肯定比(1, 1)高, 所以肯定可以容纳
             */ 
            for (auto dir : dirs) {
                int i = x + dir.first;
                int j = y + dir.second;
                if (i < 0 || j < 0 || i >= row || j >= column || visit[i][j]) continue;
                visit[i][j] = true;
                water += max(0, _max-heightMap[i][j]);
                q.push(make_pair(i, j));
            }
        }
        return water;
    }
};

int main() {
    vector<vector<int>> heightMap;
    vector<int> v1({1,4,3,1,3,2});
    vector<int> v2({3,2,1,3,2,4});
    vector<int> v3({2,3,3,2,3,1});
    heightMap.push_back(v1);
    heightMap.push_back(v2);
    heightMap.push_back(v3);
    Solution s;
    cout<<s.trapRainWater(heightMap)<<endl;
    return 0;
}
