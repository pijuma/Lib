void upd(int b, int inic, int fimm){

	if(inic <= ini[b] && fimm >= fim[b]){
		qtd[b]++ ; 
		return ; 
	}

	for(int i = max(ini[b], inic) ; i <= min(fimm, fim[b]) ; i++) v[i] = max(0LL, v[i] - 1) ; 
}

int32_t main(){

	cin >> n >> m ; 

	for(int i = 1 ; i <= n ; i++) cin >> v[i] ; 

	int sq = sqrt(n) + 1 ; 

    for(int i = 1, j = sq, k = 0 ; i <= n ; i++, j++){
    	if(j == sq){
    		k++ ; 
    		j = 0 ; 
    		ini[k] = i ; 
    	}
    	fim[k] = i ; 
    	meubloco[i] = k ; 
    }
    
    for(int i = 1 ; i <= m ; i++){
    	int x ; 
    	cin >> x ; 
    	int val = max(0LL, v[x] - qtd[meubloco[x]]) ; 
    	int l = max(x-val, 1LL) ; int r = min(n, x+val) ; 
    	for(int j = 1 ; j <= meubloco[n] ; j++) upd(j, l, r) ; 
    }

    int tot = 0 ; 
    for(int i = 1 ; i <= n ; i++) tot += max(0LL, v[i] - qtd[meubloco[i]]) ; 
    cout << tot << "\n" ; 
}