#include <bits/stdc++.h>
using namespace std;

vector<int> vet;

void kmpPreProcess(int* b, string pat){
    int i = 0, j = -1; b[0] = -1;
    
    while(i < (int)pat.size()){
        while(j >= 0 && pat[i] != pat[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

void kmpSearch(int* b, string text, string pat){
    int i = 0, j = 0;
    while(i < (int)text.size()){
        while(j >= 0 && text[i] != pat[j]) j = b[j];
        i++;j++;
        if(j == (int)pat.size()){
            vet.push_back(i-j+1);
            j = b[j];
        }
    }
}

int main(){

    int t; cin >> t;

    while(t--){
        string s1,s2; cin >> s1 >> s2;
        int b[10000];
        kmpPreProcess(b,s2);
        kmpSearch(b,s1,s2);

        if(!vet.empty()){
            cout << vet.size() << "\n";
            for(auto x : vet){
                cout << x << " ";
            }
            cout << "\n";
        }
        else{
            cout << "Not Found\n";
        }
        cout << "\n";

        vet.clear();
    }

    return 0;
}