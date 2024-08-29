//small to large basicao
//qts cores diferentes na sub de v 
set<int> sum[maxn] ; 
void dfs(int v, int p) // dfs padrao p calcular sz das comps
 
void sml(int v, int p){
 
    int mx = -1, id = -1 ; 
    for(auto a : grafo[v]){
        if(a == p) continue ; 
        if(sz[a] > mx){
            mx = sz[a] ; id = a ; 
        }
    }
 
    if(id == -1){ // eh folh
        sum[v].insert(cor[v]) ; 
        ans[v] = sum[v].size() ; 
        return ; 
    }
 
    sml(id, v) ;
 
    swap(sum[v], sum[id]) ; 
    
    //add big child 
    sum[v].insert(cor[v]) ;
  
    for(auto a : grafo[v]){ // passa por cada filho - big
        if(a == id || a == p) continue ; 
        sml(a, v) ; // vai p filho- com a resp dele arruma o atual 
        for(auto b : sum[a]){ // passa por cada cor q tem na sub do filho 
            sum[v].insert(b) ;  
        }
    }
    
    ans[v] = sum[v].size() ; 
}
 
int main(){
  
    cin >> n ;
 
    for(int i = 1 ; i <= n ; i++) cin >> cor[i] ; 
 
    for(int i = 1 ; i < n ; i++){
        int a, b ; cin >> a >> b ; 
        grafo[a].push_back(b) ; grafo[b].push_back(a) ;
    } 
 
    dfs(1, 1) ; sml(1, 1) ; 
 
    for(int i = 1 ; i <= n ; i++) cout << ans[i] << " " ; 
    cout << "\n" ; 
}
