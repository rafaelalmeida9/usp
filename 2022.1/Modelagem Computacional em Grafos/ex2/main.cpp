#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
vector<int> vertices[MAXN];
int dist[MAXN];

void bfs(int v){
    memset(dist,-1,sizeof(dist)); 
    dist[v] = 0;
    queue<int> q;
    q.push(v);

    while(q.size()){
        int front = q.front();
        q.pop();
        for(auto x : vertices[front]){
            if(dist[x] == -1){
                dist[x] = dist[front] + 1;
                q.push(x);
            }
        }
    }
}

int main(){

    int n;
    string palavra;

    cin >> palavra >> n >> palavra;

    int x,y;

    for(int i = 0;i < n-1;i++){
        cin >> x >> y;
        vertices[x].push_back(y);
        vertices[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        bfs(i);
        for(int j = 1;j <= n;j++){
            cout << dist[j] << " ";
        }
        cout << "\n";
    }



    return 0;
}