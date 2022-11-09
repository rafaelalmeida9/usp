#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[1000];
int vis[1000];
bool ciclo = false;

void dfs(int v){
    vis[v] = 1; //vértice visitado
    for(auto x: edges[v]){
        if(!vis[x]){
            dfs(x);
        }
        else if(vis[x] == 1){
            ciclo = true;
        }
    }

    vis[v] = 2; //vértice terminado
}

int main(){

    int n; cin >> n;

    for(int i=0;i<n;i++){
        int a,b; cin >> a >> b;
        edges[a].push_back(b);
    }

    for(int i = 1; i <= n; i++){
        if(!vis[i]) dfs(i);
    }

    if(ciclo){
        cout << "S\n";
    }
    else{
        cout << "N\n";
    }

    return 0;
}
