#include <bits/stdc++.h>
using namespace std;

int n;
int vet[100005];
int dp[100005];

int lis(int x){
    if(dp[x] != -1) return dp[x];
    if(x == n){
        return 0;
    }

    int MAX=0;

    for(int i=x+1;i<n;i++){
        if(vet[x] < vet[i]){
            MAX = max(MAX,lis(x+1)+1);
        }
    }
    dp[x] = MAX;

    return dp[x];
}

int main(){

    memset(dp,-1,sizeof(dp));

    cin >> n;
    for(int i=0;i<n;i++){
        cin >> vet[i];
    }
    vet[n] = vet[n-1];

    cout << lis(0) + 1 << "\n";

    return 0;
}