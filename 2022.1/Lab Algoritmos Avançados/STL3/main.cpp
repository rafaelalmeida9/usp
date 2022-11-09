#include <bits/stdc++.h>
using namespace std;

bool compara(pair<int,string> p1, pair<int,string> p2){
    if(p1.first > p2.first){
        return true;
    }
    else if(p1.first == p2.first){
        if(p1.second < p2.second){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void solve(map<string,string> student, string project[], int i){

    map<string,string>::iterator itr;

    vector<pair<int,string>> v;
    int res;

    for(int j = 0; j < i; j++){
        res = 0;
        for(itr = student.begin(); itr != student.end(); ++itr){
            if(itr->second == project[j] && itr->second != "null"){
                res++;
            }
        }
        v.push_back(make_pair(res,project[j]));
    }

    sort(v.begin(),v.end(),compara);

    for(int j = 0; j < (int)v.size(); j++){
        cout << v[j].second << " " << v[j].first << "\n";
    }

    return;
}

int main(){

    string s;
    string project[101];

    int i = 0;

    map<string,string> student;

    while(true){
        getline(cin, s);

        if(s[0] == '1'){
            solve(student,project,i);

            student.clear();
            string project[101];
            i = 0;
        }

        if(s[0] == '0') break;

        if(s[0] >= 'A' && s[0] <= 'Z'){
            project[i] = s;
            i++;
        }

        if(s[0] >= 'a' && s[0] <= 'z'){
            if(student.find(s) == student.end()){
                student.insert(make_pair(s,project[i-1]));
            }
            else if(student[s] != project[i-1]){
                student[s] = "null";
            }
        }
      
    }

    return 0;
}