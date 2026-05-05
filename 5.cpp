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