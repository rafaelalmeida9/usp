#include <iostream>
#include <stack>

using namespace std;

void invertePilha(stack <int> p){
    stack <int> temp;

    while(!p.empty()){
        temp.push(p.top());
        p.pop();
    }

    while(!temp.empty()){
        p.push(temp.top());
        temp.pop();
    }
}

void imprimePilha(stack <int> p){

    while(!p.empty()){
        cout << p.top() << "\n";
        p.pop();
    }

    return;
}

int main()
{
    int n,e,st;
    cin >> n;


    for(int i = 0; i < n; i++){

        if(i != 0) cout << "\n";

        stack <int> p;

        cin >> e;

        for(int j = 0; j < e; j++){
            cin >> st;
            p.push(st);
        }

        invertePilha(p);
        imprimePilha(p);
    }

    return 0;
}
