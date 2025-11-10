vector<int> root ; 
vector<int> e, d, lazy, sum ; 

struct SEG{

    int create(){
        e.pb(0) ; d.pb(0) ; lazy.pb(0) ; sum.pb(0) ;
        return e.size()-1 ;  
    }

    int clone(int u){
        int v = create() ; 
        e[v] = e[u], d[v] = d[u] ; 
        lazy[v] = lazy[u] ; sum[v] = sum[u] ; 
        return v ;  
    }

    void apply(int u, int add, int len){
        sum[u] = (sum[u] + add*len)%998244353 ; 
        lazy[u] = (lazy[u] + add)%998244353 ; 
    }

    void flush(int no, int i, int j){
        if(!lazy[no] || i == j || no >= e.size()) return ; 
        e[no] = clone(e[no]) ;  
        d[no] = clone(d[no]) ; 
        apply(e[no], lazy[no], meio-i+1);
        apply(d[no], lazy[no], j-meio) ; 
        lazy[no] = 0 ; 
    }

    int upd(int no, int i, int j, int a, int b, int val){
        if(i > j) return 0 ; 
        int neww = clone(no) ; 
        if(i > b || j < a) return neww ;
        if(a <= i && b >= j){
            apply(neww, val, j-i+1);
            return neww ; 
        }
        flush(neww, i, j) ; 
        if(!e[neww]) e[neww] = create(); 
        if(!d[neww]) d[neww] = create() ; 
        int aux1 = upd(e[neww], i, meio, a, b, val) ; 
        int aux2 = upd(d[neww], meio + 1, j, a, b, val) ; 
        e[neww] = aux1, d[neww] = aux2 ; 
        sum[neww] = (sum[e[neww]] + sum[d[neww]])%998244353 ; 
        return neww ; 
    }

    int query(int pos, int i, int j, int l, int r, int carry){
        if(i > r || j < l) return 0 ; 
        if(l <= i && r >= j) return (sum[pos] + (carry*(j-i+1))%998244353)%998244353; 
        int newcarry = (carry + lazy[pos])%998244353 ; 
        return (query(e[pos], i, meio, l, r, newcarry) + query(d[pos], meio + 1, j, l, r, newcarry))%998244353 ; 
    }


}Seg ; 

void dfs_built(int v, int p){
    root[v] = Seg.upd(root[p], 1, m, l[v], r[v], k[v]) ; 
    if(p != 0) tab[0][v] = p ; 
    for(auto a : grafo[v]){
        if(a == p) continue ; 
        nivel[a] = nivel[v] + 1 ; 
        dfs_built(a, v) ; 
    }
}

int lca(int a, int b){}

int query(int s, int t, int l, int r){
    if(nivel[s] > nivel[t]) swap(s, t) ; 
    int _lca = lca(s, t) ; 
    int val = Seg.query(root[t], 1, m, l, r, 0)%998244353 ; 
    if(!_lca) return val ; 
    if(_lca == s){//caminho vertical 
        if(tab[0][s] == 0 || tab[0][s] == -1) return val ; //n tem pai 
        val = (val - Seg.query(root[tab[0][s]], 1, m, l, r, 0) + 998244353)%998244353 ; 
        return val ; 
    }
    val += Seg.query(root[s], 1, m, l, r, 0) ;
    if(tab[0][_lca]!=-1){
        val = (val + 998244353 -Seg.query(root[tab[0][_lca]], 1, m, l, r, 0))%998244353 ;
    }
    val = (val - Seg.query(root[_lca], 1, m, l, r, 0) + 998244353)%998244353 ;
    return val ; 
}

int32_t main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
    cin >> n >> m ; 
    for(int i = 1 ; i < n ; i++){
        int a, b ; cin >> a >> b ; 
        grafo[a].pb(b) ; grafo[b].pb(a); 
    }
    for(int i = 1 ; i <= n ; i++){
        nivel[i] = 0 ; 
        for(int j = maxl - 1 ; j >= 0 ; j--) tab[j][i] = -1 ; 
    }

    for(int i = 1 ; i <= n ; i++) cin >> l[i] >> r[i] >> k[i] ; 
    root.pb(Seg.create()) ;
    for(int i = 1 ;i <= n ; i++) root.pb(0) ; 
    dfs_built(1, 0) ; 
    for(int i = 1; i < maxl ; i++){
        for(int j =1 ; j <=  n ; j++){
            if(tab[i-1][j] == -1) continue ; 
            tab[i][j] = tab[i-1][tab[i-1][j]]  ;
        }
    }
    int ans = 0 ; int q ; cin >> q ; 
    for(int i = 1; i <= q ; i++){
        int s, t, l, r ; cin >> s >> t >> l >> r ; 
        ans = query(s, t, l, r) ; 
        ans %= 998244353; 
        cout << ans << "\n" ; 
    }
}
