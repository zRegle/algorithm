/* Leetcdoe 54 螺旋矩阵
给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例 1:
输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]

示例 2:
输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

#include <vector>
using namespace std;

//模拟实际的过程, 遇到访问的元素则转弯
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int height = matrix.size();
        if (height == 0) return res;
        int width = matrix[0].size();
        if (width == 0) return res;
        vector<vector<bool>> visit(height+2, vector<bool>(width+2, false)); //标记矩阵
        //用一层为'true'的外壳包裹原来的矩阵, 表示不可访问
        for (int i = 0; i < width+2; i++) {
            visit[0][i] = true;
            visit[height+1][i] = true;
        }
        for (int i = 0; i < height+2; i++) {
            visit[i][0] = true;
            visit[i][width+1] = true;
        }
        int i = 1, j = 1;
        for (int cnt = 0; cnt < width*height; cnt++) {
            res.push_back(matrix[i-1][j-1]);
            visit[i][j] = true;
            bool up = visit[i-1][j], down = visit[i+1][j], left = visit[i][j-1], right = visit[i][j+1];
            if (up && left && !right) j++;
            else if (up && right && !down) i++;
            else if (down && right && !left) j--;
            else if (down && left && !up) i--;
        }
        return res;
    }
};

//更加好的解法, 在便利过程中不断调整边界, 当边界交错时, 退出循环, 这样就不需要标记数组了
class Solution2 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if(matrix.empty()) return ans; //若数组为空，直接返回答案
        int u = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;
        while(true)
        {
            for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
            if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if(-- r < l) break; //重新设定有边界
            for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
            if(-- d < u) break; //重新设定下边界
            for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
            if(++ l > r) break; //重新设定左边界
        }
        return ans;
    }
};