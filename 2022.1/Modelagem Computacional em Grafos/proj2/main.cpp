#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Aresta{
    int dist;
    int x,y;
};

struct UnionFind{

    vector<int> par;

    UnionFind(int n){
        par.resize(n + 1);

        for(int i = 1; i <= n; i++){
            par[i] = i;
        }
    }

    int find(int u){
        if(par[u] == u) return u;
        return par[u] = find(par[u]);
    }

    void unite(int u, int v){
        u = find(u);
        v = find(v);

        par[u] = v;
    }
};

bool comp(Aresta a, Aresta b){
    if(a.dist < b.dist) return true;
    else return false;
}

int main(){

    char arquivo[10],lixo[10];

    cin >> arquivo;

    FILE* file;
    file = fopen(arquivo,"r");

    int a,b,c,n;
    Aresta aresta[1000];

    fscanf(file,"%s", lixo);
    fscanf(file,"%d", &n);
    fscanf(file,"%s", lixo);

    int m = 1;

    while(fscanf(file,"%d %d %d", &a, &b, &c) != EOF){
        aresta[m].x = a;
        aresta[m].y = b;
        aresta[m].dist = c;
        m++;
    }

    sort(aresta+1,aresta+m+1,comp);

    int soma = 0;
    UnionFind uf(m);

    for(int i = 1; i < m; i++){
        if(uf.find(aresta[i].x) != uf.find(aresta[i].y)){
            uf.unite(aresta[i].x,aresta[i].y);
            soma+= aresta[i].dist;
        }
    }

    cout << soma << "\n";

    return 0;
}