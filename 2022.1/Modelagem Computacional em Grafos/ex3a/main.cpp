#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[1000];
int vis[1000];

void dfs(int v, int contador){
    vis[v] = contador;
    for(auto x: edges[v]){
        if(!vis[x]) dfs(x,contador);
    }
}

int main(){

    char arquivo[10],lixo[10];

    cin >> arquivo;

    FILE* file;
    file = fopen(arquivo,"r");

    int a,b,n;

    fscanf(file,"%s", lixo);
    fscanf(file,"%d", &n);
    fscanf(file,"%s", lixo);

    while(fscanf(file,"%d %d", &a, &b) != EOF){
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    int contador = 1;

    vector<int> componentes;

    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            dfs(i,contador);

            int vertices = 0;
            for(int j = 1; j <= 100; j++){
                if(vis[j] == contador) vertices++;
            }

            componentes.push_back(vertices);

            contador++;
        }
    }

    sort(componentes.rbegin(),componentes.rend());

    cout << componentes.size() << "\n";

    for(auto x: componentes){
        cout << x << "\n";
    }

    return 0;
}
