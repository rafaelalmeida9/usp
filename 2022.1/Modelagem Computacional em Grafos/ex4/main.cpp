#include <bits/stdc++.h>
using namespace std;
 
typedef pair<int,int> ii;
 
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
vector<ii> edges[MAXN];
int dist[MAXN];

void dijkstra(int st){
    memset(dist,INF,sizeof(dist));
 
    priority_queue<ii, vector<ii>, greater<ii>> pq;
 
    dist[st] = 0;
 
    pq.emplace(dist[st],st);
 
    while(pq.size()){
        int w1 = pq.top().first;
        int a = pq.top().second;
        pq.pop();
 
        if(dist[a] < w1) continue;
 
        for(auto x: edges[a]){
            int w2 = x.first;
            int b = x.second;
 
            if(dist[a] + w2 < dist[b]){
                dist[b] = dist[a] + w2;
                pq.emplace(dist[b],b);
            }
 
        }
 
    }
    
}

int main(){

    char arquivo[10],lixo[10];

    cin >> arquivo;

    FILE* file;
    file = fopen(arquivo,"r");

    int a,b,w,n;

    fscanf(file,"%s", lixo);
    fscanf(file,"%d", &n);
    fscanf(file,"%s", lixo);

    while(fscanf(file,"%d %d %d", &a, &b, &w) != EOF){
        int a,b,w; cin >> a >> b >> w;
        edges[a].push_back(make_pair(w,b));
        // edges[b].push_back(make_pair(w,a));
    }

    for(int i = 1; i <= n; i++){
        dijkstra(i);
        for(int j = 1; j <= n; j++){
            printf("%4d ",dist[j]);
        }
        printf("\n");
    }

    return 0;
}
