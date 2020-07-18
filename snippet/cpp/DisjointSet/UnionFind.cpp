#include <vector>

using namespace std;

class UnionFind {
    int n;
    vector<int> tree;
    vector<int> rank;

    public:
    UnionFind(int n) {
        tree.resize(n);
        for (int i = 0; i < n; i++) {
            tree[i] = i;
        }
        rank.assign(n, 1);
    }

    int find(int s) {
        if (tree[s] == s) {
            return s;
        }
        return tree[s] = find(tree[s]);
    }

    void merge(int a, int b) {
        
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        if (rank[a] > rank[b]) {
            swap(a, b);
        }

        tree[a] = b;
        if (rank[a] == rank[b]) {
            rank[b]++;
        }
    }


};