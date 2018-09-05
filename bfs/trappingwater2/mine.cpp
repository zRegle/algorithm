#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int row = heightMap.size();
        if (!row) return 0;
        int column = heightMap[0].size();
        if (!column) return 0;
        vector<vector<bool>> visit(row, vector<bool>(column, false));

        auto cmp = [&heightMap](const pair<int, int>& p1, const pair<int, int>& p2) -> bool {
            return heightMap[p1.first][p2.second] > heightMap[p2.first][p2.second];
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        for (int i = 0; i < row; i++) {
            visit[i][0] = visit[i][column-1] = true;
            q.push(make_pair(i, 0));
            q.push(make_pair(i, column-1));
        }

        for (int j = 0; j < column; j++) {
            visit[0][j] = visit[row-1][j] = true;
            if (!visit[0][j]) q.push(make_pair(0, j));
            if (!visit[row-1][j]) q.push(make_pair(row-1 , j));
        }

        vector<pair<int ,int>> dirs;
        dirs.emplace_back(make_pair(1, 0)); dirs.emplace_back(make_pair(-1, 0));
        dirs.emplace_back(make_pair(0, 1)); dirs.emplace_back(make_pair(0, -1));

        int water = 0;
        int _max = INT_MIN;
        while (!q.empty()) {
            auto c = q.top(); q.pop();
            int x = c.first, y = c.second;
            _max = max(_max, heightMap[x][y]);
            for (auto dir : dirs) {
                int _x = x + dir.first;
                int _y = y + dir.second;
                if (_x < 0 || _y < 0 || _x >= row || _y >= column || visit[_x][_y]) continue;
                visit[_x][_y] = true;
                water += max(0, _max - heightMap[_x][_y]);
                q.push(make_pair(_x ,_y));
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