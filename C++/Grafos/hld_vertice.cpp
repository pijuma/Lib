long long n, q, val[maxn], tree[4*maxn], nivel[maxn], pos[maxn], pai[maxn], sz[maxn] ;
long long head[maxn], ct, c, cam[maxn] ; 
vector<int> grafo[maxn] ; 
 
struct SEG{
 
	void upd(int no, int i, int j, int pos, int valor){
		if(i == j){
			tree[no] = valor ; 
			return ; 
		}
		if(pos <= meio) upd(esq, i, meio, pos, valor) ; 
		else upd(dir, meio + 1, j, pos, valor) ; 
		tree[no] = max(tree[esq], tree[dir]) ; 
	}
 
	long long query(int no, int i, int j, int a, int b){
		if(i > b || j < a) return 0 ; 
		if(i >= a && j <= b) return tree[no] ; 
		return max(query(esq, i, meio, a, b), query(dir, meio + 1, j, a, b)) ;  
	}
 
} Seg ; 
 
void dfs(int v, int p){
	
	sz[v] = 1 ; pai[v] = p ; 
 
	for(auto a : grafo[v]){
		if(a == p) continue ; 
		nivel[a] = nivel[v] + 1 ; 
		dfs(a, v) ; 
		sz[v] += sz[a] ; 
	}
 
}
 
void hld(int v){
 
	if(!head[c]) head[c] = v ; // cabou de criar um novo caminho 
	cam[v] = c, pos[v] = ++ct ;
 
	Seg.upd(1, 1, n, pos[v], val[v]) ; 
 
	int mx = -1, id = -1 ; 
 
	for(auto a : grafo[v]){
		if(a == pai[v]) continue ; 
		if(mx < sz[a]) mx = sz[a], id = a ; 
	} 
 
	if(id != -1) hld(id) ; // continua pro maior 
 
	for(auto a : grafo[v]){
		if(a == pai[v] || a == id) continue ; 
		c++ ; hld(a) ; // cria um novo 
	}
 
}
 
 
int lca(int a, int b){
 
	while(cam[a] != cam[b]){
		if(nivel[head[cam[a]]] > nivel[head[cam[b]]]) a = pai[head[cam[a]]] ;
		else b = pai[head[cam[b]]] ; 
	}
 
	if(nivel[a] > nivel[b]) return b ;
	return a ; 
 
}
 
long long query_path(int a, int b){
 
	long long ans = 0LL ; 
 
	while(cam[a] != cam[b]){
		ans = max(ans, Seg.query(1, 1, n, pos[head[cam[a]]], pos[a])) ; 
		a = pai[head[cam[a]]] ; 
	}
 
	if(pos[a] == pos[b]) return max(ans, Seg.query(1, 1, n, pos[a], pos[a])) ; 
	return max(ans, Seg.query(1, 1, n, pos[b], pos[a])) ; 
}
 
int query(int a, int b){
	int l = lca(a, b) ; 
	return max(query_path(a, l), query_path(b, l)) ; 
}
 
int main(){
 
	ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
 
	cin >> n >> q ; 
 
	for(int i = 1 ; i <= n ; i++) cin >> val[i] ; 
 
	for(int i = 1 ; i < n ; i++){
		int a, b ; cin >> a >> b ; 
		grafo[a].push_back(b) ; grafo[b].push_back(a) ;
	}
 
	dfs(1, 0) ;
	hld(1) ; 
 
	while(q--){
		int t, a, b ; cin >> t >> a >> b ;
		if(t == 1) Seg.upd(1, 1, n, pos[a], b) ;
		else cout << query(a, b) << " " ;  
	}
 
	cout << "\n" ;

}
