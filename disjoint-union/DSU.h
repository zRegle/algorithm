#include <vector>
using std::vector;

#ifndef DSU_H
#define DSU_H

class DSU {
public:
    explicit DSU(int n) {
        father.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        return x == father[x] ? x : (father[x] = find(father[x]));
    }

    int merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) return 0;
        if (rank[x] >= rank[y])
            father[y] = x;
        else
            father[x] = y;
        if (rank[x] == rank[y])
            rank[x]++;
        return 1;
    }

private:
    vector<int> father;
    vector<int> rank;
};

#endif //DSU_H