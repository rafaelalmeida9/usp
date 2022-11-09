#include <bits/stdc++.h>
using namespace std;

int main(){

    int t; cin >> t;

    while(t--){
        string s; cin >> s;

        int player = 0; //0-alice 1-bob

        for(int i = 0; i < (int)s.size(); i++){
            if(player == 0){

                if(s[i] == 'a') s[i] = 'b';
                else s[i] = 'a';

                player = 1;
            }
            else{

                if(s[i] == 'z') s[i] = 'y';
                else s[i] = 'z';

                player = 0;
            }
        }

        cout << s << "\n";
    }

    return 0;
}