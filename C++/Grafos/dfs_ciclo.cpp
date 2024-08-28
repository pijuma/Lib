void dfs(int v, int p){
	vis[v] = 1 ; 
	for(auto a : grafo[v]){
		if(ciclo) continue ; 
        	//if(a == p) continue ; - em aresta bidirecionada n pode voltar pela mesma 
		pai[a] = v ; 
		if(vis[a] == 1){
			ciclo = v ; pai[a] = 0 ; 
		} 
		else if(!vis[a]) dfs(a, v) ; 
	}
	vis[v] = 2 ; 
}
 
void redo(int x){ //recuperar começando em "ciclo" 
	if(!x) return ; 
	redo(pai[x]) ; 
	cam.push_back(x) ; 
}
 
int main(){
	cin >> n >> m ; 
	for(int i = 1 ; i <= m ; i++){
		int a, b ; cin >> a >> b ; 
		grafo[a].push_back(b) ; //grafo[b].push_back(a) ;
	}
 
	for(int i = 1 ; i <= n ; i++){
		if(!vis[i]) dfs(i, -1) ; 
	}
 
	if(!ciclo){ cout << "IMPOSSIBLE\n" ; exit(0) ; } 
	else{
		cam.push_back(ciclo) ; redo(ciclo) ; 
		cout << cam.size() << "\n" ;  
		for(auto a : cam) cout << a << " " ; 
	}
 
}
