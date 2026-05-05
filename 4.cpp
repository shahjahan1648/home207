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