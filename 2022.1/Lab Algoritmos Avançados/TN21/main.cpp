#include <bits/stdc++.h>
using namespace std;

int vet[100005];

int mdc(int num1, int num2) {

    int resto;

    do {
        resto = num1 % num2;

        num1 = num2;
        num2 = resto;

    } while (resto != 0);

    return num1;
}

int main(){

    int n; cin >> n;

    for(int i=0;i<n;i++){
        cin >> vet[i];
    }

    vector<int> vet2;

    for(int i=1;i<n;i++){
        vet2.push_back(vet[i]-vet[i-1]);
    }

    sort(vet2.begin(),vet2.end());

    int res = mdc(vet2[0],vet2[1]);
    cout << (vet[n-1] - n - 1)/res - 1 << "\n";

    return 0;
}