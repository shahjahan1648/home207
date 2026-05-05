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