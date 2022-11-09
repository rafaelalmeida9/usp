#include <bits/stdc++.h>
using namespace std;

int n,m;
int k;
string s;
char grid[6][6];
bool aux[6][6];

bool res = false;

void solve(int i, int j, int x, char grid[6][6]){
    if(!aux[i][j]) return;
    if(x == k - 1 && grid[i][j] == s[x]){
        res = true;
        return;
    }
    if(grid[i][j] != s[x]) return;

    aux[i][j] = false;

    if(i + 1 < n) solve(i+1,j,x+1,grid);
    if(i - 1 >= 0) solve(i-1,j,x+1,grid);
    if(j + 1 < m) solve(i,j+1,x+1,grid);
    if(j - 1 >= 0) solve(i,j-1,x+1,grid);

    aux[i][j] = true;
}

int main(){

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            aux[i][j] = true;
        }
    }

    cin >> n >> m;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }

    cin >> k;
    cin >> s;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            solve(i,j,0,grid);
        }
    }

    if(res) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}