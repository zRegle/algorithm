#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
 * leetcode 417. Pacific Atlantic Water Flow
 * 给定一个m x n的矩阵, 每个元素代表那个格子的高度, 矩阵的上方和左边是太平洋, 下方和右边是大西洋
 * 海水只能从高流向低, 或者在相同高度的两个格子流过, 求出所有既能流向太平洋, 也能流向大西洋的格子
 * 例如:
 * Pacific ~  ~  ~  ~  ~
 *      ~  1  2  2  3 (5) *
 *      ~  3  2  3 (4)(4) *
 *      ~  2  4 (5) 3  1  *
 *      ~ (6)(7) 1  4  5  *
 *      ~ (5) 1  1  2  4  *
 *         *  *  *  *  * Atlantic
 * 结果: [[0,4], [1,3], [1,4], [2,2], [3,0], [3,1], [4,0]]
 *       带括号的就是符合要求的格子
 *
 * 思路: bfs, 分别两个队列, 两个二维数组
 * 首先将太平洋和大西洋的"元素"分别塞进对应的队列里, 然后bfs搜索
 * 同时记录哪些元素是遍历过符合要求的
 */

class Soultion {
	vector<pair<int, int>> direction;	//方向数组
	int row, column;
			
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		vector<pair<int, int>> res;
		row = matrix.size();
		if (!row) return res;
		column = matrix[0].size();
		if (!column) return res;

		queue<pair<int, int>> pQueue, aQueue;	//分别保存可以到达太平洋和大西洋的坐标
		vector<vector<bool>> pacific(row, vector<bool>(column, false));	//可以流到太平洋的坐标
		vector<vector<bool>> atlantic(row, vector<bool>(column, false));	//可以流到大西洋的坐标

		for (int i = 0; i < row; i++) {
			pQueue.push(pair<int, int>(i, 0));	//太平洋左边界
			aQueue.push(pair<int, int>(i, column-1));	//大西洋右边界
			pacific[i][0] = true;
			atlantic[i][column-1] = true;
		}

		for (int i = 0; i < column; i++) {
			pQueue.push(pair<int, int>(0, i));	//太平洋上边界
			aQueue.push(pair<int, int>(row-1, i));	//大西洋下边界
			pacific[0][i] = true;
			atlantic[row-1][i] = true;
		}

		direction.emplace_back(pair<int, int>(1, 0));	//down
		direction.emplace_back(pair<int, int>(-1, 0));	//top
		direction.emplace_back(pair<int, int>(0, 1));	//right
		direction.emplace_back(pair<int, int>(0, -1));	//left

		bfs(pQueue, matrix, pacific);
		bfs(aQueue, matrix, atlantic);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (pacific[i][j] && atlantic[i][j])
					res.emplace_back(pair<int, int>(i, j));
			}
		}
		return res;
	}

	void bfs(queue<pair<int, int>>& q, vector<vector<int>>& matrix, vector<vector<bool>>& visited) {
		while (!q.empty()) {
			auto coordinate = q.front(); q.pop();
			for (auto dir : direction) {
				int x = coordinate.first + dir.first;
				int y = coordinate.second + dir.second;
				if (x < 0 || x >= row || y < 0 || y >= column 
					|| visited[x][y] || matrix[x][y] < matrix[coordinate.first][coordinate.second]) 
					continue;
				visited[x][y] = true;
				q.push(pair<int, int>(x, y));              
			}
		}
	}
};