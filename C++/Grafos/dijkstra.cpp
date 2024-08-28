priority_queue< pii, vector<pii>, greater<pii> > fila;

void dijkstra(int k){
    d[k] = 0;
    fila.push({0, k});

    while(!fila.empty()){
        auto [w, u] = fila.top();
        fila.pop();
        if (used[u]) continue;
        used[u] = true;

        for(auto [v, w]: g[u]){
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                fila.push({d[v], v});   
            }
        }
    }
}
//k menores caminhos de 1 a n: 
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fila ; 
fila.push({0, 1}) ; 

while(!fila.empty()){
    int at = fila.top().second ; int d = fila.top().first ; fila.pop() ; 
    if(dist[at].size() > k) continue ; //n qro mais de k 
    dist[at].push_back(d) ; //mais um jeito de chegar em at 
    for(auto a : grafo[at]) fila.push({d + a.second, a.first}) ; 
}
