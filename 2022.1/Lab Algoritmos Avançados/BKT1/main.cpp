#include <bits/stdc++.h>
using namespace std;

int n;
int res = 0;
vector<int> vet;

void subset(int i, int atual){
    if(i == n){
        res += atual;
        return;
    }

    subset(i+1,atual);

    atual = atual^vet[i];

    subset(i+1,atual);
}

int main(){

    cin >> n;

    for(int i=0;i<n;i++){
        int v; cin >> v;
        vet.push_back(v);
    }

    subset(0,0);

    cout << res << "\n";

    return 0;
}