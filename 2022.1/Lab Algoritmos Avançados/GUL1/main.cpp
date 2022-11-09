#include <bits/stdc++.h>
using namespace std;

int main(){

    int n,m;

    while(true){
        cin >> n >> m;

        if(n == 0 && m == 0) break;

        vector<int> dragon;
        vector<int> knight;

        int tmp;

        for(int i = 0; i < n; i++){
            cin >> tmp;
            dragon.push_back(tmp);
        }

        for(int i = 0; i < m; i++){
            cin >> tmp;
            knight.push_back(tmp);
        }

        sort(dragon.begin(),dragon.end());
        sort(knight.begin(),knight.end());

        int i = 0, j = 0, money = 0;

        while(i != (int)dragon.size() && j != (int)knight.size()){
            if(knight[j] >= dragon[i]){
                money += knight[j];
                i++; j++;
            }
            else{
                j++;
            }
        }

        if(i == (int)dragon.size()){
            cout << money << "\n";
        }
        else{
            cout << "Loowater is doomed!\n";
        }
    }

    return 0;
}