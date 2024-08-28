void dfs(int u, int p){
	vis[u] = 1 ; 
	pai[u] = p ; 
	for(int a : grafo[u]){
		if(a == p) continue ; 
		if(vis[a]){
			vector<int> ans ; 
			int p = u ; 
			while(a^u){
				ans.pb(u) ; 
				u = pai[u] ;  
			}
			ans.pb(a), ans.pb(p) ; 
			cout << ans.size() << "\n" ; 
			for(int b : ans) cout << ++b << " " ; 
			cout << "\n" ; 
			exit(0) ; 
		}
	    else dfs(a, u) ; 
	}
