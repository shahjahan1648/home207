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