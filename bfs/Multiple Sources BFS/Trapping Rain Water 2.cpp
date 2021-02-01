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
 * 核心思想就是不断套用"木桶原理"，先确定木桶的外围，
 * 找到外围的最短板子后对其周围能填水的地方填水，然后更新木桶外围
 */
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define IS_IN(x, y) (x >= 0 && y >= 0 && x < row && y < column)
#define ID(x, y) (x * column + y)
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int row = heightMap.size(), column = heightMap[0].size();
        //一个格子有四个木板作为边界, 可能之前某个格子已经计算过容纳多少水了, 所以需要标记数组
        vector<int> visited(row * column);   
        //最小堆
        auto cmp = [&](const int pos1, const int pos2) -> bool {
            int i = pos1 / column, j = pos1 % column;
            int k = pos2 / column, l = pos2 % column;
            return heightMap[i][j] > heightMap[k][l];
        };
        priority_queue<int, vector<int>, decltype(cmp)> q(cmp);   //边界队列
        int tmp;
        //把矩阵的左右两边入队列
        for (int i = 0; i < row; i++) {
            tmp = ID(i, 0);
            visited[tmp] = 1; q.push(tmp);
            tmp = ID(i, column - 1);
            visited[tmp] = 1; q.push(tmp);
        }
        //把矩阵的上下两边入队列
        for (int j = 0; j < column; j++) {
            tmp = ID(0, j);
            visited[tmp] = 1; q.push(tmp);
            tmp = ID(row - 1, j);
            visited[tmp] = 1; q.push(tmp);
        }
        //以上两个循环就构成了最初的容器

        //方向数组
        int dirs[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

        int water = 0;
        int borderMax = INT_MIN; //边界的最短木板高度
        //从最初的容器逐步收缩, 最终收缩到一个点
        while (!q.empty()) {
            int pos = q.top(); q.pop();  //去除边界中最短的那块木板
            int x = pos / column, y = pos % column;
            //因为我们是从外围逐渐收缩, 所以如果遇到了更高的板子, 我们应该更新变量, 作为内圈的最短板子
            borderMax = max(borderMax, heightMap[x][y]);  

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
            for (auto& dir : dirs) {
                int i = x + dir[0], j = y + dir[1];
                if (IS_IN(i, j)) {
                    tmp = ID(i, j);
                    if (visited[tmp] == 0) {
                        visited[tmp] = 1;
                        /* borderMax - height[i][j]可能小于0
                         * 意思是(i, j)不能灌水
                         * 因此需要与0进行max
                         */
                        water += max(0, borderMax - heightMap[i][j]);
                        //(i, j)作为新的边界加入队列
                        q.push(tmp);
                    }
                }
            }
        }
        return water;
    }
};