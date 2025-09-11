int n, mxlvl, k1, k2 ; 
ll ans ; 
ll bit[maxn] ; 
int sz[maxn], vis[maxn], min_d[maxn], nivel[maxn] ; 
int pai[maxn], cor[maxn] ; 
vector<int> grafo[maxn] ; 
 
struct BIT{
 
    void upd(int pos, int val){
        for(; pos < maxn ; pos += pos&-pos) bit[pos] += val ; 
    }
 
    int query(int l, int r){
        int valr = 0 ; l-- ;
        for(; r > 0 ; r -= r&-r) valr += bit[r] ; 
        int vall = 0 ; 
        if(l) for(; l > 0 ; l -= l&-l) vall += bit[l] ; 
        return valr - vall ;     
    }
 
} Bit ; 
 
void dfs(int v, int p){
    
    sz[v] = 1 ; 
 
    for(auto a : grafo[v]){
        if(a == p || vis[a]) continue ;
        dfs(a, v) ; sz[v] += sz[a] ; 
    }
 
}
 
void reroot(int neww, int old){
    if(old == -1) return ; 
    sz[old] -= sz[neww] ; 
    sz[neww] += sz[old] ; 
}
 
int find_cent(int v, int szz, int p){
 
    for(auto a : grafo[v]){
        if(a == p || vis[a] || 2*sz[a] <= szz) continue ; 
        reroot(a, v) ; 
        return find_cent(a, szz, v) ; 
    }
 
    return v ; 
 
}
 
void add(int t, int v, int p, int lvl){
 
    if(lvl > k2) return ; 
 
    mxlvl = max(mxlvl, lvl) ; 
 
    if(t) ans += Bit.query(max(1, k1-lvl+1), k2-lvl+1) ; 
    else Bit.upd(lvl+1, 1) ;
 
    for(auto a : grafo[v]){
        if(a == p || vis[a]) continue ; 
        add(t, a, v, lvl+1) ; 
    }
 
}
 
void make_cent(int v, int p = -1){
 
    int cent = find_cent(v, sz[v], p) ; 
    vis[cent] = 1 ; 
 
    mxlvl = 0 ; 
    Bit.upd(1, -Bit.query(1, 1) + 1) ; 
 
    for(auto a : grafo[cent]){
        if(a == p || vis[a]) continue ; 
        add(1, a, cent, 1) ; 
        add(0, a, cent, 1) ; 
    }
 
    for(int i = 1 ; i <= mxlvl ; i++) Bit.upd(i+1, -Bit.query(i+1, i+1)) ; 
 
    for(auto a : grafo[cent]){
        if(a == cent || vis[a]) continue ; 
        make_cent(a, cent) ; 
    }
    
}
 
int main(){
 
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
 
    cin >> n >> k1 >> k2 ;
 
    for(int i = 1 ; i < n ; i++){
        int a, b ; cin >> a >> b ; 
        grafo[a].push_back(b) ; grafo[b].push_back(a) ; 
    }
 
    dfs(1, -1) ; 
    make_cent(1) ; 
 
    cout << ans << "\n" ; 
 
}
