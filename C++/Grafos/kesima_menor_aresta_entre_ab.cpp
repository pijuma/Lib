// dado uma arvore 
// queremos a kth menor aresta do caminho de a pra b 
int n, q, w[maxn], mx, vis[maxn], tab[maxl][maxn], nivel[maxn] ;
vector<int> grafo[maxn], e, d, root, sum ;

struct SEG{

    int create(){
        e.push_back(0) ; d.push_back(0) ; sum.push_back(0) ;
        return max(0, (int)e.size() - 1) ;
    }

    int upd(int no, int i, int j, int pos, int v){

        int neww = create() ;
        e[neww] = e[no], d[neww] = d[no], sum[neww] = sum[no] ;

        if(i == j){
            sum[neww]++ ;
            return neww ;
        }

        if(pos <= meio){
            int aux = upd(e[neww], i, meio, pos, v) ;
            e[neww] = aux ;
        }

        else{
            int aux = upd(d[neww], meio + 1, j, pos, v) ;
            d[neww] = aux ;
        }

        sum[neww] = sum[e[neww]] + sum[d[neww]] ;
        return neww ;

    }

    int query(int no_a, int no_b, int no_lca, int val_lca, int i, int j, int k){ //késima menor aresta
        if(i == j) return i ;
        int vesq = sum[e[no_a]] + sum[e[no_b]] - 2*sum[e[no_lca]] + (val_lca <= meio && val_lca >= i) ;
        if(vesq >= k) return query(e[no_a], e[no_b], e[no_lca], val_lca, i, meio, k) ;
        else return query(d[no_a], d[no_b], d[no_lca], val_lca, meio + 1, j, k - vesq) ;
    }

} Seg ;

void dfs(int v, int p){

    vis[v] = 1 ;

    for(auto a : grafo[v]){
        if(a == p || vis[a]) continue ;
        nivel[a] = nivel[v] + 1 ;
        tab[0][a] = v ;
        dfs(a, v) ;
    }

}

void build_seg(int v, int p){

    int aux = Seg.upd(root[p], 1, mx, w[v], 1) ;

    root[v] = aux ;

    for(auto a : grafo[v]){
        if(a == p) continue ;
        build_seg(a, v) ;
    }

}

int lca(int u, int v){

    if(nivel[v] > nivel[u]) swap(u, v) ;

    for(int i = maxl - 1 ; i >= 0 ; i--){
        if(tab[i][u] != -1 && nivel[tab[i][u]] >= nivel[v]) u = tab[i][u] ;
    }

    if(u == v) return u ;

    for(int i = maxl - 1 ; i >= 0 ; i--){
        if(tab[i][v] != -1 && tab[i][u] != -1 && tab[i][v] != tab[i][u]) u = tab[i][u], v = tab[i][v] ;
    }

    return tab[0][v] ;

}

int main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ;

    cin >> n >> q ;

    root.push_back(Seg.create()) ;
    for(int i = 1 ; i <= n ; i++) root.push_back(0) ;

    for(int i = 1 ; i <= n ; i++){
        cin >> w[i] ; mx = max(mx, w[i]) ;
    }

    for(int i = 0 ; i <= n ; i++){
        for(int j = 0 ; j < maxl ; j++){
            tab[j][i] = -1 ;
        }
    }

    for(int i = 1 ; i < n ; i++){
        int u, v, w ;
        cin >> u >> v ;
        grafo[u].push_back(v) ; grafo[v].push_back(u) ;
    }

    dfs(1, 0) ;
    build_seg(1, 0) ;

    for(int i = 1 ; i < maxl ; i++){
        for(int j = 1 ; j <= n ; j++){
            if(tab[i-1][j] == -1) continue ;
            tab[i][j] = tab[i-1][tab[i-1][j]] ;
        }
    }

    while(q--){
        int u, v, k ;
        cin >> k >> u >> v ;
        int _lca = lca(u, v) ;
        //cout << lca << "\n" ;
        cout << Seg.query(root[u], root[v], root[_lca], w[_lca], 1, mx, k) << "\n" ;
    }

}
