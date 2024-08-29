void bfs(int v){
	queue<pair<int,int>> fila ; fila.push({v, 0}) ;
	memset(dist, 0, sizeof dist) ; 
	dist[v] = 1 ;
	while(!fila.empty()){
		int at = fila.front().first, p = fila.front().second ; fila.pop() ; 
		for(auto a : grafo[at]){
			if(a == p) continue ; 
			if(!dist[a]){
				dist[a] = dist[at] + 1 ; 
				fila.push({a, at}) ; 
			}
			else mn = min(mn, dist[at] + dist[a] - 1) ;
		}
	}
}
