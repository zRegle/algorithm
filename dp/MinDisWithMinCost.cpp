#include <iostream>
#include <climits>
#include <queue>
using namespace std;

struct edge {
    int weight;
    int cost;
};

/**
 * 最短路径 + 最小花费:
 * 每条路有一定的长度,经过每一条路要收取对应的路费,如果钱不够就不能通过
 * 可能存在某一条路的长度小于另外一条路,但是收取的路费要高一点
 * 现在手上有一定数额的钱,求一条最短路径并且花费最少
 *
 * 利用动态规划:
 * dp[i][j]表示从起点出发到达顶点i的最短距离,并且剩下j元
 */

/**
 * 找出未被遍历的状态中,拥有最短路径的状态
 * @param dp 动规数组
 * @param visit 判断状态是否被遍历过
 * @param n 顶点个数
 * @param money 最初有多少钱
 * @return pair<int, int> 第一个元素代表顶点,第二个元素代表还剩多少钱
 */
pair<int, int>* findMin(int** dp, bool** visit, int n, int money) {
    int min = INT_MAX;
    pair<int, int>* p = new pair(-1, -1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= money; ++j) {
            if (!visit[i][j] && min > dp[i][j]) {
                min = dp[i][j];
                p->first = i;
                p->second = j;
            }
        }
    }
    return p;
}
/**
 * 迪杰斯特拉算法·改
 * @param dis 邻接矩阵,每一个元素代表一条边,有着对应的路长和路费
 * @param n 顶点个数
 * @param money 最初有多少钱
 * @return pair<int, int> 第一个元素代表最短路径的长度,第二个元素代表剩下多少钱
 */
pair<int, int>* dij(edge** dis, int n, int money) {
    int** dp = new int*[n + 1];
    bool** visit = new bool*[n + 1];
    for (int i = 1; i <= n; ++i) {  //顶点下标从1开始
        dp[i] = new int[money + 1];
        visit[i] = new bool[money + 1];
        for (int j = 0; j <= money; ++j) {  //剩下的钱可能为0,所以从0开始
            dp[i][j] = INT_MAX;
            visit[i][j] = false;
        }
    }
    //从起点到起点,并且剩下money元,最短距离为0
    dp[1][money] = 0;
    while (true) {
        pair<int, int>* p = findMin(dp, visit, n, money);
        int vertex = p->first;
        int left = p->second;
        //如果找不到符合要求的状态,退出循环
        if (vertex == -1 && left == -1) break;
        //状态被遍历过,但不一定就要经过这个点
        visit[vertex][left] = true;
        //对找到的那个顶点,遍历其可达的顶点
        for (int i = 1; i <= n; ++i) {
            edge* e = &dis[vertex][i];
            if (e->weight != INT_MAX) {
                //若i可达
                if (left - e->cost >= 0 &&
                dp[i][left - e->cost] > dp[vertex][left] + e->weight)
                    /**
                     * 这里要重点理解
                     * dp[vertex][left] + e->weight的意思是通过点vertex到达点i的最短距离
                     * 那么通过点vertex到达i后,钱还剩下left - e->cost
                     * 所以如果dp[i][left - e->cost] > dp[vertex][left] + e->weight
                     * 就要更新路径信息了
                     */
                    dp[i][left - e->weight] = dp[vertex][left] + e->weight;
            }
        }
    }
    //找出拥有最短距离的路径
    int min_dis = INT_MAX;
    for (int k = 0; k <= money; ++k) {
        min_dis = min(dp[n][k], min_dis);
    }
    int max_left = -1;
    //遍历这些路径,找出剩下钱最多的
    for (int l = 0; l <= money; ++l) {
        if (dp[n][l] == min_dis && max_left < l)
            max_left = l;
    }
    for (int m = 1; m <= n; ++m) {
        delete[](dp[m]);
        delete[](visit[m]);
    }
    delete[](dp); delete[](visit);
    return new pair<int, int>(min_dis, max_left);
}

/**
 * 第一行输入三个数,分别代表顶点个数,边的条数,以及最初有多少钱
 * 接下来每一行有四个数,分别代表起点,终点,边的权重,边的花费
 */
int main() {
    int n, m, money;
    cin>>n>>m>>money;
    edge** dis = new edge*[n + 1];
    for (int i = 1; i <= n; ++i) {
        dis[i] = new edge[n + 1];
    }
    for (int j = 0; j < m; ++j) {
        int a, b, weight, cost;
        cin>>a>>b>>weight>>cost;
        edge* e = new edge();
        e->weight = weight;
        e->cost = cost;
        dis[a][b] = *e;
    }
    pair<int, int>* p = dij(dis, n, money);
    cout<<"min distance: "<<p->first<<" "<<"min cost: "<<p->second<<endl;
    for (int k = 1; k <= n; ++k) {
        delete[](dis[k]);
    }
    delete[](dis);
    return 0;
}