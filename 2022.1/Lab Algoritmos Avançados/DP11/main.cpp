#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int n;
int vet[100005];
int dp[100005];

long long solve(int x){
    if(dp[x] != -1) return dp[x];
    if(x == n){
        return INF;
    }
    if(x == n-1){
        return 0;
    }

    dp[x] = min(abs(vet[x+1]-vet[x]) + solve(x+1),abs(vet[x+2]-vet[x]) + solve(x+2));

    return dp[x];
}

int main(){

    memset(dp,-1,sizeof(dp));

    cin >> n;
    for(int i=0;i<n;i++){
        cin >> vet[i];
    }
    vet[n] = vet[n-1];

    cout << solve(0) << "\n";

    return 0;
}