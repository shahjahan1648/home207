#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int N = 20;

int final_path[N];
bool visited[N];
int final_res = INT_MAX;

// Function to copy solution
void copyToFinal(int curr_path[], int n) {
    for (int i = 0; i < n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0];
}

// Calculate lower bound (simple version)
int firstMin(vector<vector<int>> &adj, int i, int n) {
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
        if (adj[i][k] != 0 && adj[i][k] < min)
            min = adj[i][k];
    return min;
}

int secondMin(vector<vector<int>> &adj, int i, int n) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (i == j) continue;

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] < second && adj[i][j] != first) {
            second = adj[i][j];
        }
    }
    return second;
}

// Branch and Bound function
void TSPRec(vector<vector<int>> &adj, int curr_bound, int curr_weight,
            int level, int curr_path[], int n) {

    if (level == n) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight +
                           adj[curr_path[level - 1]][curr_path[0]];

            if (curr_res < final_res) {
                copyToFinal(curr_path, n);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {

            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1], n) +
                                firstMin(adj, i, n)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1], n) +
                                firstMin(adj, i, n)) / 2);

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path, n);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            // Reset visited
            for (int j = 0; j < n; j++)
                visited[j] = false;
            for (int j = 0; j < level; j++)
                visited[curr_path[j]] = true;
        }
    }
}

// Main TSP function
void TSP(vector<vector<int>> &adj, int n) {

    int curr_path[N];
    int curr_bound = 0;

    for (int i = 0; i < n; i++)
        curr_bound += (firstMin(adj, i, n) + secondMin(adj, i, n));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    for (int i = 0; i < n; i++)
        visited[i] = false;

    curr_path[0] = 0;
    visited[0] = true;

    TSPRec(adj, curr_bound, 0, 1, curr_path, n);
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> adj[i][j];

    TSP(adj, n);

    cout << "\nMinimum cost: " << final_res << endl;
    cout << "Path: ";
    for (int i = 0; i <= n; i++)
        cout << final_path[i] << " ";

    return 0;
}