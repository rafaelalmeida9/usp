#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

string a,b;
string dp[MAXN][MAXN];

string lcs(int i, int j){
    if(dp[i][j] != "*") return dp[i][j];

    if(i >= (int)a.size() || j >= (int)b.size()) return "";

    if(a[i] == b[j]){
        dp[i][j] = max(lcs(i+1,j+1)+a[i],max(lcs(i+1,j),lcs(i,j+1)));
    }
    else{
        dp[i][j] =  max(lcs(i+1,j),lcs(i,j+1));
    }

    return dp[i][j];
}

int main(){

    for(int i = 0; i < 3005; i++){
        for(int j = 0; j < 3005; j++){
            dp[i][j] = "*";
        }
    }

    cin >> a >> b;

    string res = lcs(0,0);

    reverse(res.begin(),res.end());

    cout << res << "\n";

    return 0;
}