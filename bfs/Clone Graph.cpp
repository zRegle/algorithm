/* Leetcode 133.克隆图
 * 给你无向连通图中一个节点的引用，请你返回该图的 深拷贝（克隆）。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

//BFS, DFS解法参考DFS文件夹
class Solution1 {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<Node*, Node*> map; //旧节点->新节点的映射
        queue<Node*> q;
        auto newNode = new Node(node->val);
        map[node] = newNode;
        q.push(node);
        while (!q.empty()) {
            int cnt = q.size();
            while (cnt--) {
                auto rootOld = q.front(); q.pop();
                auto rootCopy = map[rootOld];
                for (auto neighbor : rootOld->neighbors) {
                    if (map.find(neighbor) == map.end()) {
                        auto n = new Node(neighbor->val);
                        map[neighbor] = n;
                        rootCopy->neighbors.push_back(n);
                        q.push(neighbor);
                    } else {
                        //map[neighbor]->rootCopy的映射在之前已经建立好了
                        //现在需要建立root->Copy->map[neighbor]的映射
                        rootCopy->neighbors.push_back(map[neighbor]);
                    }
                }
            }
        }
        return newNode;
    }
};