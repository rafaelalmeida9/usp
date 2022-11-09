#include <bits/stdc++.h>
using namespace std;

int main(){

    int t; cin >> t;

    while(t--){
        int m; cin >> m;

        int x = 0;

        for(int i = 0; i < m; i++){
            int s; cin >> s;
            x = x ^ s;
        }

        if(x == 0){
            cout << "1\n";
        }
        else cout << "0\n";
    }

    return 0;
}