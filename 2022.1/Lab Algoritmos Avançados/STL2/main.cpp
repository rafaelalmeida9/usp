#include <bits/stdc++.h>
using namespace std;

int main(){

    int t;
    cin >> t;

    int n,m;

    for(int i = 0; i < t; i++){
        int cont = 0;
        
        cin >> n >> m;

        deque<pair<int,int>> dq;

        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            dq.push_back(make_pair(x,j));
        }

        while(!dq.empty()){
            for(int j = 0; j < (int)dq.size(); j++){
                if(dq[j].first > dq[0].first){
                    int end = dq[0].first;
                    int endpos = dq[0].second;
                    dq.pop_front();
                    dq.push_back(make_pair(end,endpos));
                    
                    j = 0;
                }
            }

            cont++;

            if(dq[0].second == m){
                break;
            }

            dq.pop_front();
        }

        cout << cont << "\n";
    }

    return 0;
}