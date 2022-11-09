#include <bits/stdc++.h>
using namespace std;

long long sum(int x){
    return (x*(x-1))/2;
}

int main(){

    long long n; cin >> n;
    int res;

    int i = 0;

    while(true){
        if(sum(i) == n){
            res = i-1;
            break;
        }
        else if(sum(i) > n){
            res = i-2;
            break;
        }
        i++;
    }

    cout << res << "\n";

    return 0;
}