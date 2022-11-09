#include <bits/stdc++.h>
using namespace std;

int main(){

    int t; cin >> t;

    for(int i = 0; i < t; i++){
        int n; cin >> n;

        vector<int> vet;

        for(int j = 0; j < n; j++){
            int x; cin >> x;
            vet.push_back(x);
        }

        int maxres = 0;

        for(int j = 0; j < n; j++){
            set<int> st;
            int res = 0;
            for(int k = j; k < n; k++){
                if(st.find(vet[k]) == st.end()){
                    st.insert(vet[k]);
                    res++;
                }
                else break;
            }
            st.clear();
            maxres = max(maxres,res);
        }

        cout << maxres << "\n";
    }

    return 0;
}