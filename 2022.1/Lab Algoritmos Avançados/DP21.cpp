#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int n;

int a[MAXN];
int b[MAXN];
int c[MAXN];

long long dp[MAXN][5];

long long solve(int x, int last){
    if(x == n) return 0;
    if(dp[x][last] != 0) return dp[x][last];

    if(last == 1){
        dp[x][last] = max(solve(x+1,2) + b[x],solve(x+1,3) + c[x]);
    }
    else if(last == 2){
        dp[x][last] = max(solve(x+1,1) + a[x],solve(x+1,3) + c[x]);
    }
    else if(last == 3){
        dp[x][last] = max(solve(x+1,1) + a[x],solve(x+1,2) + b[x]);
    }
    else if(last == 0){
        dp[x][last] = max(solve(x+1,1) + a[x],max(solve(x+1,2) + b[x],solve(x+1,3) + c[x]));
    }

    return dp[x][last];
}

int main(){

    cin >> n;

    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i] >> c[i];
    }

    cout << solve(0,0) << "\n";

    return 0;
}
