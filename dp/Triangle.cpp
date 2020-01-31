#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/**
 * leetcode 120 Triangle
 * 给定一个三角形, 求从顶到底的最短路径之和, 每一步只能走到下一行相邻的数字
 * 例如:
 *    2
 *   3,4
 *  6,5,7
 * 4,5,6,3
 * 输出: 2+3+5+5=15
 *
 * 思路: 用动态规划解决即可, 两个数组, 一个数组保存上一行的结果, 一个用来处理当前行的结果
 * 上面那个例子, 整理一下就变成
 * 2
 * 3,4
 * 6,5,7
 * 4,5,6,3
 * 在处理(i, j)时候, 只能从(i-1, j-1)或者(i-1, j)走过来, 我们每次都取较小的, 然后注意一下边界条件即可
 */ 

class Solution {
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        if (!row) return 0;
        auto first = triangle[0];
        if (!first.size()) return 0;
        vector<int> prev(first);
        vector<int> cur(first.size()+1, 0);
        for (int i = 1; i < row; i++) {
            int prev_size = triangle[i-1].size();
            int cur_size = triangle[i].size();
            for (int j = 0; j < cur_size; j++) {
                int prev_left = j-1 >= 0 ? prev[j-1] : prev[j];
                int prev_right = j < prev_size ? prev[j] : prev[j-1];
                cur[j] = min(prev_left, prev_right) + triangle[i][j];
            }
            prev.clear(); prev.swap(cur);
            cur.resize(cur_size+1);
        }
        int minSum = INT_MAX;
        for (int sum : prev) minSum = min(minSum, sum);
        return minSum;
    }
};

/**
 * 更简单的做法, 只用一个数组, 空间复杂度是O(n)
 */
class MoreEfficientSolution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		vector<int> minSum(triangle.back());	//三角形的最后一行初始化
		int N = triangle.size();	//行数
		for (int level = N-2; level >= 0; level--)	//从倒数第二行开始, 自底向上
			for (int index = 0; index <= level; index++)	//第几层就有多少个元素
				minSum[index] = min(minSum[index], minSum[index+1]) + triangle[level][index];
		return minSum[0];	
	}
};

/**
 * 升级版: 求路径
 */
 class Solution2 {
 public:
    vector<int> minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        if (!row) {
            vector<int> v;
            return v;
        }
        auto first = triangle[0];
        if (first.empty()) {
            vector<int> v;
            return v;
        }
        //上一行的最短路径, 这一行的最短路径
        vector<vector<int>> prev_path;
        prev_path.emplace_back(first);
        vector<vector<int>> cur_path(first.size()+1);
        for (int i = 1; i < row; i++) {
            auto prev_value = triangle[i-1];    //上一行的原始数值
            auto cur_value = triangle[i];   //当前行的数值
            int cur_size = cur_value.size();
            int prev_size = prev_value.size();
            for (int j = 0; j < cur_size; j++) {
                int prev_left = j-1 >= 0 ? j-1 : j; //获取下标
                int prev_right = j < prev_size ? j : j-1;   //获取下标
                vector<int> new_path;   //新的路径
                //比较, 然后拷贝一份
                if (prev_value[prev_left] < prev_value[prev_right]) {
                    new_path.assign(prev_path[prev_left].begin(), prev_path[prev_left].end());
                } else {
                    new_path.assign(prev_path[prev_right].begin(), prev_path[prev_right].end());
                }
                //新路径加入当前的格子的数值
                new_path.push_back(cur_value[j]);
                //添加新路径
                cur_path[j] = new_path;
            }
            prev_path.clear(); prev_path.swap(cur_path);
            cur_path.resize((unsigned int)cur_size+1);
            //swap和assign的区别:
            //A.swap(B) -> 将A的内容替换成B的内容, B会清空
            //A.assign(B.begin(), B.end()) -> 将A的内容替换成B的内容, B不变
        }
        //各路径求和, 返回最小值
        int minSum = INT_MAX, minIndex = -1;
        for (int i = 0; i < prev_path.size(); i++) {
            int sum = 0;
            for (auto num : prev_path[i]) sum += num;
            if (sum < minSum) {
                minSum = sum;
                minIndex = i;
            }
        }
        return prev_path[minIndex];
    }
 };
