#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(Matrix A , Matrix B){
    int n = A.size();
    Matrix C(n , vector<int>(n));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix sub(Matrix A , Matrix B){
    int n = A.size();
    Matrix C(n , vector<int>(n));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

Matrix strassen(Matrix A , Matrix B){
    int n = A.size();

    if(n==1){
        return{{A[0][0]*B[0][0]}};
    }

    int k = n/2;

    Matrix A11(k , vector<int>(k)) , A12(k , vector<int>(k)) , A21(k , vector<int>(k)) , A22(k , vector<int>(k));
    Matrix B11(k , vector<int>(k)) , B12(k , vector<int>(k)) , B21(k , vector<int>(k)) , B22(k , vector<int>(k));
    
    for(int i  = 0 ; i < k ; i++){
        for(int j = 0 ; j < k ; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    Matrix M1 = strassen(add(A11 , A22) , add(B11 , B22));
    Matrix M2 = strassen(add(A21 , A22) , B11);
    Matrix M3 = strassen(A11, sub(B12 , B22));
    Matrix M4 = strassen(A22, sub(B21 , B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(sub(A21 , A11) , add(B11 , B12));
    Matrix M7 = strassen(sub(A12 , A22) , add(B21 , B22));

    Matrix C11 = add(sub(add(M1 , M4) , M5) , M7);
    Matrix C12 = add(M3 , M5);
    Matrix C21 = add(M2 , M4);
    Matrix C22 = add(sub(add(M1 , M3) , M2) , M6);
    
    Matrix C(n , vector<int>(n));
    for(int i  = 0 ; i < k ; i++){
        for(int j = 0 ; j < k ; j++){
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }
    return C;

}

void printMatrix(Matrix M){
    for(auto row:M){
        for(auto val:row){
            cout<<val<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int n;
    cout << "Enter size of matrix (power of 2): ";
    cin >> n;

    Matrix A(n, vector<int>(n)), B(n, vector<int>(n));

    cout << "Enter Matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter Matrix B:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    Matrix C = strassen(A, B);

    cout << "Resultant Matrix:\n";
    printMatrix(C);
    return 0;
}

2)
#include <iostream>
using namespace std;

// Function using Divide & Conquer
void findMinMax(int arr[], int low, int high, int &minVal, int &maxVal) {

    // Base Case 1: One element
    if (low == high) {
        minVal = maxVal = arr[low];
        return;
    }

    // Base Case 2: Two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            minVal = arr[low];
            maxVal = arr[high];
        } else {
            minVal = arr[high];
            maxVal = arr[low];
        }
        return;
    }

    // Divide
    int mid = (low + high) / 2;

    int min1, max1, min2, max2;

    // Conquer
    findMinMax(arr, low, mid, min1, max1);
    findMinMax(arr, mid + 1, high, min2, max2);

    // Combine
    minVal = (min1 < min2) ? min1 : min2;
    maxVal = (max1 > max2) ? max1 : max2;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int minVal, maxVal;

    findMinMax(arr, 0, n - 1, minVal, maxVal);

    cout << "Minimum element: " << minVal << endl;
    cout << "Maximum element: " << maxVal << endl;

    return 0;
}




3)
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of files: ";
    cin >> n;

    int files[n];

    cout << "Enter file sizes:\n";
    for (int i = 0; i < n; i++) {
        cin >> files[i];
    }

    // Greedy step: sort in ascending order
    sort(files, files + n);

    cout << "\nOptimal order of storing files:\n";
    for (int i = 0; i < n; i++) {
        cout << files[i] << " ";
    }

    // Calculate Mean Retrieval Time (MRT)
    int sum = 0, total = 0;

    for (int i = 0; i < n; i++) {
        sum += files[i];
        total += sum;
    }

    float mrt = (float)total / n;

    cout << "\nMean Retrieval Time: " << mrt << endl;

    return 0;
}






4)
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node{
    char data;
    int freq;
    Node* left , *right;

    Node(char d , int f){
        data = d;
        freq = f;
        left = right = NULL;
    }
};

struct compare{
    bool operator()(Node* l , Node* r){
        return l->freq > r->freq;
    }
};

void printcodes(Node*root , string code){
    if(!root) return;

    if(root->data != '$'){
        cout<<root->data<<" : "<< code << endl;
    }

    printcodes(root->left , code+"0");
    printcodes(root->right , code+"1");

}

int main(){
    int n ;
    cout<<"Enter number of characters: ";
    cin>>n;

    vector<int> freq(n);
    vector<char> chars(n);

    cout<<"Enter Characters :\n";
    for(int i = 0 ; i < n ; i++){
        cin>>chars[i];
    }

    cout<<"Enter Frequencies :\n";
    for(int i = 0 ; i < n ; i++){
        cin>>freq[i];
    }

    priority_queue<Node* , vector<Node*> , compare> pq;

    for(int i = 0 ; i < n ; i++){
        pq.push(new Node(chars[i] , freq[i]));
    }

    while(pq.size() > 1){
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('$' , left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();
    cout<<"\nHuffman Codes:\n";
    printcodes(root , "");
}




5)
#include<iostream>;
#include<string>;
#include<vector>;
using namespace std;

int main(){
    string x , y;
    cout<<"Enter first string : ";
    cin>>x;
    cout<<"Enter second string : ";
    cin>>y;

    int m = x.size();
    int n = y.size();

    vector<vector<int>>dp(m+1 , vector<int>(n+1 , 0));

    for(int i = 1 ; i <= m ; i ++){
        for(int j = 1 ; j <= n ; j++){
            if(x[i-1] == y[j-1]){
                dp[i][j]  = 1+dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
            }
        }
    }

    cout<<"Length of longest common subsequence is : "<<dp[m][n]<<endl;

    int i = m ; 
    int j = n ;
    string lcs = "";

    while(i>0 && j>0){
        if(x[i-1] == y[j-1]){
            lcs = x[i-1]+lcs;
            i--;
            j--;
        } else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        } else {
            j--;
        }
    }
    cout<<"Longest common subsequence is : "<<lcs<<endl;
}




6)
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct edge{
    int u , v , w;
};

void printPath(int v , vector<int>&parent){
    if(v==-1) return;
    printPath(parent[v] , parent);
    cout<<v<<" ";
}

int main(){
    int V , E;
    cout<<"Enter number of vertices and edges : ";
    cin>>V>>E;

    vector<edge> edges(E);
    cout<<"Enter edges (u v w) :\n";
    for(int i = 0 ; i < E ; i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }

    int source;
    cout<<"Enter source vertex : ";
    cin>>source;

    vector<int> dist(V,INT_MAX);
    vector<int> parent(V,-1);

    dist[source] = 0;

    for(int i = 1 ; i < V-1 ; i++){
        for(int j = 0 ; j < E ; j++){
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    for(int j = 0 ; j < E ; j++){
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
            cout<<"Negative weight cycle detected!"<<endl;
            return 0;
        }
    }

    cout << "\nVertex\tDistance\tPath\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t";
        if (dist[i] == INT_MAX) {
            cout << "INF\t\tNo Path\n";
        } else {
            cout << dist[i] << "\t\t";
            printPath(i, parent);
            cout << endl;
        }
    }

}






7)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> wt(n), val(n);

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter knapsack capacity: ";
    cin >> W;

    // DP table
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum value: " << dp[n][W] << endl;

    return 0;
}




8)
#include <iostream>
using namespace std;

const int MAX = 20;
int board[MAX][MAX];

// Check if it's safe to place a queen
bool isSafe(int row, int col, int n) {

    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function
bool solveNQueens(int row, int n) {

    // Base case: all queens placed
    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {

        if (isSafe(row, col, n)) {

            board[row][col] = 1; // place queen

            if (solveNQueens(row + 1, n))
                return true;

            board[row][col] = 0; // backtrack
        }
    }

    return false;
}

// Print solution
void printBoard(int n) {
    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    // Initialize board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    if (solveNQueens(0, n))
        printBoard(n);
    else
        cout << "No solution exists\n";

    return 0;
}





9)
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




10)
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