#include <iostream>
#include <vector>
using namespace std;

bool hamiltonianPath(vector<vector<int>> &graph, int V) {
    vector<int> path(V, -1);
    vector<bool> visited(V, false);

    path[0] = 0;          // start from vertex 0
    visited[0] = true;

    int pos = 1;

    while (pos >= 1) {
        bool found = false;

        // Try next vertex
        for (int v = path[pos] + 1; v < V; v++) {

            // Check if safe
            if (!visited[v] && graph[path[pos - 1]][v] == 1) {

                // Backtrack undo if needed
                if (path[pos] != -1)
                    visited[path[pos]] = false;

                path[pos] = v;
                visited[v] = true;
                found = true;
                break;
            }
        }

        if (found) {
            if (pos == V - 1) {
                // Solution found
                cout << "Hamiltonian Path: ";
                for (int i = 0; i < V; i++)
                    cout << path[i] << " ";
                cout << endl;
                return true;
            }
            pos++;
            path[pos] = -1; // reset next position
        } else {
            // Backtrack
            visited[path[pos]] = false;
            path[pos] = -1;
            pos--;
        }
    }

    return false;
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    if (!hamiltonianPath(graph, V))
        cout << "No Hamiltonian Path exists\n";

    return 0;
}