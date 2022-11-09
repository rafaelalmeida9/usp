#include <bits/stdc++.h>
using namespace std;

int main(){

    while(true){
        
        int n; cin >> n;

        if(n == 0) break;

        int sum = 0;

        priority_queue<int, vector<int>, greater<int>> pq;

        for(int i = 0; i < n; i++){
            int x; cin >> x;
            pq.push(x);
        }

        int a,b;

        while(pq.size() != 2){
            a = pq.top();
            pq.pop();
            b = pq.top();
            pq.pop();
            pq.push(a+b);
            sum += (a + b);
        }

        a = pq.top();
        pq.pop();
        b = pq.top();
        pq.pop();

        sum += (a + b);

        cout << sum << "\n";
    }

    return 0;
}