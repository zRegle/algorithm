/* Leetcode 133.克隆图
 * 给你无向连通图中一个节点的引用，请你返回该图的 深拷贝（克隆）。
 */
#include <iostream>
#include <vector>
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

//DFS, BFS解法参考BFS文件夹
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        auto newNode = new Node(node->val);
        map[node] = newNode;
        dfs(node, newNode);
        return newNode;
    }
private:
    unordered_map<Node*, Node*> map; //旧节点->新节点的映射
    /**
     * dfs遍历图并拷贝
     * @param old 旧节点
     * @param copy 新拷贝的节点
     */
    void dfs(Node* old, Node* copy) {
        for (Node* neighbor : old->neighbors) {
            unordered_map<Node*, Node*>::iterator it;
            if ((it = map.find(neighbor)) == map.end()) {
                //该邻居还没被遍历过
                auto newNode = new Node(neighbor->val);
                map[neighbor] = newNode;
                //填充copy的邻居
                copy->neighbors.push_back(newNode);
                dfs(neighbor, newNode);
            } else {
                //这个邻居在之前的深度里被遍历过了
                //只建立了neighbor->copy的邻居关系, 现在要建立copy->neighbor的邻居关系
                copy->neighbors.push_back(it->second);
            }
        }
    }
};