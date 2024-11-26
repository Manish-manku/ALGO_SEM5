#include <iostream>
#include <vector>
#include <climits> 
using namespace std;

struct Edge {
    int src, dest, weight;
};

// Bellman-Ford Algorithm
void bellmanFord(int V, int E, int source, const vector<Edge> &edges) {
    // Initialize distances from source to all vertices as infinite
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Relax all edges (V - 1) times
    for (int i = 1; i <= V - 1; i++) {
        for (const auto &edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int w = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto &edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int w = edge.weight;
        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "Graph contains a negative-weight cycle!" << endl;
            return;
        }
    }

    // Print the shortest distances
    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << "        " << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges;
    cout << "Enter the edges (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(V, E, source, edges);

    return 0;
}
