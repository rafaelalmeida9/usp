#include <bits/stdc++.h>
using namespace std;

long long minimum(vector<int> vet){

    vector<long long> vet2;

    for(int i = 0; i < (int)vet.size(); i++){
        if(vet[i] > 0) vet2.push_back(vet[i]);

        else if(vet[i] == -2){
            vet2[vet2.size()-1] *= (long long)vet[i+1];
            i++;
        }
    }

    long long sum = 0;

    for(int i = 0; i < (int)vet2.size(); i++){
        sum += vet2[i];
    }

    return sum;
}

long long maximum(vector<int> vet){

    vector<long long> vet2;

    for(int i = 0; i < (int)vet.size(); i++){
        if(vet[i] > 0) vet2.push_back(vet[i]);

        else if(vet[i] == -1){
            vet2[vet2.size()-1] += (long long)vet[i+1];
            i++;
        }
    }

    long long mult = 1;

    for(int i = 0; i < (int)vet2.size(); i++){
        mult *= vet2[i];
    }

    return mult;
}

int main(){

    int n;
    cin >> n;

    string s;

    for(int i = 0; i < n; i++){
        cin >> s;

        vector<int> vet;

        for(int j = 0; j < (int)s.size(); j++){

            if(s[j] == '+') vet.push_back(-1);

            else if(s[j] == '*') vet.push_back(-2);

            else if(s[j+1] == '+' || s[j+1] == '*' || s[j+1] == '\0'){
                vet.push_back(s[j] - '0');
            }

            else{
                int num = (s[j] - '0')*10 + (s[j+1] - '0');
                vet.push_back(num);
                j++;
            }
        }

        cout << "The maximum and minimum are " << maximum(vet) << " and " << minimum(vet)<< "." << "\n";
        
    }

    return 0;
}