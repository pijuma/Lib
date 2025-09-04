bitset<maxn> dp[maxn] ;  
void dfs(int v, int p){
 
	dp[v].reset() ; dp[v].set(v) ;
	vis[v] = 1 ; 
 
	for(auto a : grafo[v]){
		if(a == p) continue ; 
		if(!vis[a]) dfs(a, v) ; 
		dp[v] |= dp[a] ; 
	} 
 
}

//quantos nós o vertice i alcança? 
for(int i = 1 ; i <= n ; i++){
  timer++ ;
  dfs(i, i) ; 
  cout << dp[i].count() << " " ;
}
