// no vis[i] -> guarda o primeiro cara antes de ir p i 
// se vis[i] ta marcado e vamos p ele dnv eh pq temos um ciclo e é smp o menor 
// ent marcamos ans e colocamos vis como inf 
// inicialmente vis = -1 
 
queue<int> path ; 
 
void dfs(int v){
 
	path.push(v) ; 
 
	if(vis[v]){
		steps += ans[v] ; 
		return ; 
	}
 
	vis[v] = 1 ; 
	steps++ ; 
	
	dfs(grafo[v][0]) ; 
 
}
 
int main(){
 
	cin >> n ; 
 
	for(int i = 1 ; i <= n ; i++){
		cin >> a ; 
		grafo[i].push_back(a) ; 
	}
 
	for(int i = 1 ; i <= n ; i++){
		
		if(!vis[i]){
			
			steps = 0 ; 
			dfs(i) ; 
			
			int dec = 1 ;
 
			while(!path.empty()){
				
				if(path.front() == path.back()){
					dec = 0 ; 
				}
 
				ans[path.front()] = steps ; 
				steps -= dec ; 
				path.pop() ; 
 
			}
 
		}
 
	} 
 
	for(int i = 1 ; i <= n ; i++) cout << ans[i] << " " ; 
	cout << "\n" ; 
 
}
