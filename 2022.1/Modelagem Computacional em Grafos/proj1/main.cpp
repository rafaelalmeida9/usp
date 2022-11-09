#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[1000];
bool ehValido[1000];

//Verifica se o elemento v pertence ao subconjunto de vértices
bool ehSubconjunto(int v, vector<int> subconjunto){
    for(auto x: subconjunto){
        if(x == v) return true;
    }

    return false;
}

int main(){

    for(int i = 0; i < 1000; i++){ //torna todos os vértices inicialmente válidos
        ehValido[i] = true;
    }

    string lixo;
    int a,b,n;

    cin >> lixo;
    cin >> n;
    cin >> lixo;

    while(cin >> a >> b){
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    vector<int> subconjunto; //adiciona ao vetor de subconjuntos todos os subconjuntos indicados no exercícios
    subconjunto.push_back(1); subconjunto.push_back(2); subconjunto.push_back(4);
    subconjunto.push_back(8); subconjunto.push_back(9); subconjunto.push_back(10);
    subconjunto.push_back(12); subconjunto.push_back(13); subconjunto.push_back(14);

    for(int i = 1; i <= n; i++){
        if(ehSubconjunto(i,subconjunto)){ //checa se o vértice é do subconjunto
            for(auto x : edges[i]){
                if(ehSubconjunto(x,subconjunto) && ehValido[i] && ehValido[x]){ //checa se um vértice do subconjunto foi encontrado
                    cout << x << "\n";
                    ehValido[x] = false; //invalida o vértice encontrado
                }
            }
        }
    }

    return 0;
}