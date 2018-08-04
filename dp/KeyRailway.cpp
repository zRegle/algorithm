//
// Created by Administrator on 2018/8/3.
//

#include <vector>
#include <iostream>
#include <climits>
using namespace std;

/**
 * 有n个城市,城市和城市之间有m条铁路
 * 现在要找出一条铁路,将它升级为高铁路线,减少从某个城市出发到达另外一个城市所需的时间
 * 升级高铁后,原来所需的时间减少为原来的一半
 * 找出这条铁路的编号,并计算升级后所需的时间
 * PS:铁路是双向的
 *
 * 思路:
 * 实质上就是求最短路径并记录下路径信息,最后遍历最短路径中的边,找出权重最大的边
 */

struct edge {
    int id;
    int weight;
};

//从起点到终点的最短路径
struct path {
    //经过的边
    vector<edge> edges;

    void addEdge(edge e) {
        edges.push_back(e);
    }

    /**
     * 更换最短路径,原来的路径不经过点v
     * @param otherPath  从源点到点v的路径
     * @param newEdge 从点v到终点的边
     */
    void changePath(path* otherPath, edge* newEdge) {
        edges.clear();
        edges.shrink_to_fit();
        for (edge e : otherPath->edges)
            edges.push_back(e);
        edges.push_back(*newEdge);
    }
};

/**
 * 寻找从起点出发,拥有最短距离且还未被遍历的顶点
 * @param edges 起点到各个顶点的边,不可达的点的边的距离为INT_MAX
 * @param visit 用于确认哪些顶点未被遍历
 * @param size 顶点的个数 + 1
 * @return  拥有最短距离且还未被遍历的顶点的坐标
 */
int getMinDisVertex(edge* edges, bool* visit, int size) {
    int min = INT_MAX, index = -1;
    for (int i = 1; i < size; ++i) {
        if (!visit[i] && edges[i].weight <= min) {
            index = i;
            min = edges[i].weight;
        }
    }
    //可能会返回不可达的顶点
    return index;
}

/**
 * dijkstra算法, 确定最短距离并保存路径信息
 * @param matrix 邻接矩阵
 * @param from  起点
 * @param vNum  顶点个数
 * @param p 起点到各个顶点的路径数组
 */
void dij(edge** matrix, int from, int vNum, path* p) {
    int count = 1;  //已遍历的顶点(顶点已被遍历)
    bool* visit = new bool[vNum + 1];   //确认哪些顶点未被遍历
    visit[from] = true;
    edge* dis = matrix[from];   //起点到各个顶点的距离
    while (count < vNum) {
        int index = getMinDisVertex(dis, visit, vNum + 1);
        visit[index] = true; count++;
        int base_dis = matrix[from][index].weight;  //起点到新的被遍历的点的距离
        if (base_dis != INT_MAX) {  //如果该点可达,设该点为v
            edge* index_dis = matrix[index];    //v到各定点的距离
            for (int i = 1; i < vNum + 1; i++) {
                if (index_dis[i].weight != INT_MAX) {   //v到该点可达
                    int new_dis = index_dis[i].weight + base_dis;   //从起点出发,经过v点到达该点的距离
                    if (new_dis < matrix[from][i].weight) {
                        matrix[from][i].weight = new_dis;
                        p[i].changePath(&p[index], &index_dis[i]);  //更换路径
                    }
                }
            }
        }
    }
    delete[](visit);
}

/**
 * 寻找当前路径中拥有最大权重的边
 * @param p 从源点到终点的最短路径
 * @return 权重最大的边(关键路径)的下标
 */
int getKeyRailWay(path* p) {
    vector<edge> edges = p->edges;
    int max_weight = INT_MIN, index = -1;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].weight > max_weight) {
            max_weight = edges[i].weight;
            index = i;
        }
    }
    return index;
}

int main() {
    int n, m, from, to;
    cin>>n>>m>>from>>to;
    edge** matrix = new edge*[n + 1];
    for (int i = 0; i < n + 1; ++i) {
        matrix[i] = new edge[n + 1];
        for (int j = 1; j < n + 1; ++j) {
            if (i == j) {
                matrix[i][j].weight = 0;
                continue;
            }
            matrix[i][j].weight = INT_MAX;
        }
    }
    for (int j = 0; j < m; ++j) {
        int a, b, weight;
        cin>>a>>b>>weight;
        edge* e = new edge();
        e->id = j + 1;
        e->weight = weight;
        matrix[a][b] = *e;
        matrix[b][a] = *e;
    }
    path* p = new path[n + 1];
    for(int i = 1; i < n + 1; i++) {
        if (from == i) continue;
        if (matrix[from][i].weight != INT_MAX)
            p[i].addEdge(matrix[from][i]);
    }
    dij(matrix, from, n, p);
    int index = getKeyRailWay(&p[to]);
    edge* key_railway = &(p[to].edges[index]);
    cout<<"key railway: "<<key_railway->id<<endl;
    cout<<"new min dis: "<<matrix[from][to].weight - (key_railway->weight / 2)<<endl;
    for (edge e : p[to].edges)
        cout<<e.weight<<" ";
    for (int k = 0; k < n + 1; ++k) {
        delete[](matrix[k]);
    }
    delete[](matrix);
    delete[](p);
    return 0;
}