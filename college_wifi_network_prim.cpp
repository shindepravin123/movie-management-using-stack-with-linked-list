#include <iostream>
using namespace std;

#define V 6
#define INF 999999

int main()
{
    // Adjacency matrix representing installation costs
    // between college Wi-Fi access points (in thousand rupees).
    // 0 means there is no direct connection.
    int graph[V][V] = {
        {0, 4, 3, 7, 0, 0},
        {4, 0, 2, 5, 6, 0},
        {3, 2, 0, 4, 8, 9},
        {7, 5, 4, 0, 3, 6},
        {0, 6, 8, 3, 0, 5},
        {0, 0, 9, 6, 5, 0}
    };

    const char accessPoint[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

    int parent[V];
    int key[V];
    bool visited[V] = {false};

    // Initialize all key values to infinity.
    for (int i = 0; i < V; i++)
    {
        key[i] = INF;
    }

    // Start Prim's algorithm from access point A.
    key[0] = 0;
    parent[0] = -1;

    // Build the Minimum Spanning Tree with V - 1 edges.
    for (int count = 0; count < V - 1; count++)
    {
        int minKey = INF;
        int u = -1;

        // Find the unvisited vertex with the smallest key.
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        visited[u] = true;

        // Update the minimum costs of adjacent unvisited vertices.
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 &&
                !visited[v] &&
                graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Display the selected connections and calculate total cost.
    int totalCost = 0;

    cout << "MINIMUM COST COLLEGE WI-FI NETWORK\n";
    cout << "\nSelected Connections:\n";

    for (int i = 1; i < V; i++)
    {
        int cost = graph[i][parent[i]];

        cout << accessPoint[parent[i]] << " - " << accessPoint[i]
             << " : " << cost << " thousand rupees\n";

        totalCost += cost;
    }

    cout << "\nTotal Minimum Installation Cost = "
         << totalCost << " thousand rupees\n";

    cout << "Total Cost = Rs. " << totalCost * 1000 << '\n';

    return 0;
}
