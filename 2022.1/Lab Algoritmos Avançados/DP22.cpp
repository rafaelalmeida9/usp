#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int n,k;
long long w[105],v[105];

long long dp[105][MAXN];

long long solve(int i, int W){
    if(dp[i][W] != -1) return dp[i][W];
    if(i == n) return 0;

    if(W+w[i] <= k){
        dp[i][W] = max(solve(i+1,W+w[i]) + v[i], solve(i+1,W));
    }
    else{
        dp[i][W] = solve(i+1,W);
    }

    return dp[i][W];
}

int main(){
    memset(dp,-1,sizeof(dp));

    cin >> n >> k;

    for(int i=0;i<n;i++){
        cin >> w[i] >> v[i];
    }

    cout << solve(0,0) << "\n";

    return 0;
}
