class Solution {
public:
    bool isValid(int x, int y, int m, int n) {
        if (x < 0 || y < 0 || x >= m || y >= n) {
            return false;
        }
        return true;
    }

    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) {
            return 0;
        }
        int n = heightMap[0].size();
        if (n == 0) {
            return 0;
        }

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        auto comp = [&heightMap](const pair<int, int> &a, const pair<int, int> &b) {
            return heightMap[a.first][a.second] > heightMap[b.first][b.second];
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
        int count = 0;
        for (int i = 0; i < m; i++) {
            if (!visited[i][0]) {
                pq.push(make_pair(i, 0));
                visited[i][0] = true;
                count++;
            }
            if (!visited[i][n - 1]) {
                pq.push(make_pair(i, n - 1));
                visited[i][n - 1] = true;
                count++;
            }
        }

        for (int j = 0; j < n; j++) {
            if (!visited[0][j]) {
                pq.push(make_pair(0, j));
                visited[0][j] = true;
                count++;
            }
            if (!visited[m - 1][j]) {
                pq.push(make_pair(m - 1, j));
                visited[m - 1][j] = true;
                count++;
            }
        }

        vector<int> row {-1, 0, 1, 0};
        vector<int> col {0, -1, 0, 1};
        int water = 0;
        int maxCount = INT_MIN;
        while (count != m * n) {
            auto it = pq.top();
            pq.pop();
            int x = it.first;
            int y = it.second;
            maxCount = max(maxCount, heightMap[x][y]);
            for (int i = 0; i < row.size(); i++) {
                if (isValid(x + row[i], y + col[i], m, n) && !visited[x + row[i]][y + col[i]]) {
                    if (heightMap[x + row[i]][y + col[i]] < maxCount) {
                        water += maxCount - heightMap[x + row[i]][y + col[i]];
                    }
                    visited[x + row[i]][y + col[i]] = true;
                    pq.push(make_pair(x + row[i], y + col[i]));
                    count++;
                }
            }
        }
        return water;
    }
};