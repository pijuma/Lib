//maior soma de valores de 1 a n: 
void bell(int s){
    
    for(int i = 1 ; i <= n ; i++) d[i] = -inf ; d[s] = 0 ;  
    for(int i = 1 ; i <= n ; i++){
    	for(int j = 1 ; j <= m ; j++){
            if(d[u[j]] == -inf) continue ; 
    		if(d[u[j]] + w[j] > d[v[j]]) d[v[j]] = d[u[j]] + w[j] ;
    	}
    }

    for(int i = 1 ; i <= n ; i++){
    	for(int j = 1 ; j <= m ; j++){
    		if(d[u[j]] != -inf && d[u[j]] + w[j] > d[v[j]]) d[v[j]] = inf ;
    	}
    }
}
//achar ciclo negativo e recuperar:
void bell_man(){
 
    vector<pair<int,pair<int,int>>> grafo ; 
    for(int i = 1 ; i <= m ; i++) cin >> u[i] >> v[i] >> w[i] ; 
    for(int i = 1 ; i <= n ; i++) dist[i] = inf ; 
    dist[1] = 0 ; 
    
    int kra = 0 ; 

    for(int i = 1 ; i <= n ; i++){
        kra = 0 ; 
    	for(int j = 1 ; j <= m ; j++){//tentar relaxar n-1 x na prox se der é pq tem ciclo -> recupero o ultimo do ciclo 
    		if(d[u[j]] + w[j] < d[v[j]]){ 
                pai[v[j]] = u[j] ;
                d[v[j]] = d[u[j]] + w[j] ;
                kra = v[j] ; 
            } 
    	}
    }
    
    if(!kra) cout << "NO\n" ; 
    else{
        int f = kra ; 
    	cout << "YES\n" ; 
    	
    	vector<int> cycle ; 
    	
    	for(int i = 1 ; i <= n ; i++) f = pai[f] ; 
    	for(int x = f ; ; x = pai[x]){
    		cycle.push_back(x) ; 
    		if(x == f && cycle.size() > 1) break ;  
    	}
 
    	reverse(cycle.begin(), cycle.end()) ; 

    	for(int i = 0 ; i < cycle.size() ; i++) cout << cycle[i] << " " ; 
    	cout << "\n" ; 
 
    }
}
