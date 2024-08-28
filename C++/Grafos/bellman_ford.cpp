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
//achar ciclo negativo: 
bool bel(int s){

	for(int i = 0 ; i <= n ; i++) d[i] = inf ; 
	d[s] = 0 ; 

    for(int i = 0 ; i < n ; i++){
    	for(int j = 0 ; j < m ; j++){
    		if(d[u[j]] + w[j] < d[v[j]]) d[v[j]] = d[u[j]] + w[j] ; 
    	}
    }

    for(int i = 0 ; i < m ; i++){
    	if(d[u[i]] + w[i] < d[v[i]]) return true ; 
    }

    return false ; 

}

int main(){

	cin >> n >> m ; 

	for(int i = 0 ; i < m ; i++) cin >> u[i] >> v[i] >> w[i] ; 

	if(bel(u[0])) cout << "S\n" ; 
	else cout << "N\n" ; 

}
