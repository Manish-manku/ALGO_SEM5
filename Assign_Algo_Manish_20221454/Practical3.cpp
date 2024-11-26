#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Disjoint Set (Union-Find) data structure
class DisjointSet {
public:
    vector<int> parent, rank;

    // Constructor
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;  // Initially, each vertex is its own parent
        }
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    // Union by rank
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Kruskal's Algorithm
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<Edge> kruskal(int n, vector<Edge>& edges) {
    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end());

    DisjointSet ds(n);
    vector<Edge> mst;

    // Step 2: Process each edge
    for (const auto& edge : edges) {
        int u = edge.u, v = edge.v, weight = edge.weight;

        // If u and v are not in the same set, add the edge to the MST
        if (ds.find(u) != ds.find(v)) {
            ds.unionSet(u, v);  // Union the sets
            mst.push_back(edge); // Add edge to MST
        }
    }

    return mst;
}

int main() {
    // Number of vertices
    int n = 4;

    // List of edges (u, v, weight)
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find MST using Kruskal's Algorithm
    vector<Edge> mst = kruskal(n, edges);

    // Print the edges in the MST
    cout << "Edges in MST:" << endl;
    int totalWeight = 0;
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
