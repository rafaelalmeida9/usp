#include <bits/stdc++.h>
using namespace std;

vector<int> vet;
set<long long> st;
int n,q;

long long solve(int i, int j){

    if(i == j){
        st.insert(vet[i]);
        return vet[i];
    }

    int mid = (vet[i] + vet[j])/2;
    int pos = upper_bound(vet.begin()+i,vet.begin()+j,mid) - vet.begin() - 1;

    long long sum = 0;

    if(vet[i] == vet[j]){
        for(int k = i; k<=j;k++){
            sum += vet[i];
        }
    }
    else{
        sum = solve(i,pos) + solve(pos+1,j);
    }

    st.insert(sum);

    return sum;
}

int main(){

    int t; cin >> t;
    for(int i=0;i<t;i++){
        cin >> n >> q;

        for(int j=0;j<n;j++){
            int v; cin >> v;
            vet.push_back(v);
        }

        sort(vet.begin(),vet.end());

        long long sum = solve(0,vet.size()-1);
        st.insert(sum);

        for(int j=0;j<q;j++){
            int x; cin >> x;
            if(st.find(x) == st.end()){
                cout << "No\n";
            }
            else{
                cout << "Yes\n";
            }
        }

        vet.clear();
        st.clear();
    }

    return 0;
}