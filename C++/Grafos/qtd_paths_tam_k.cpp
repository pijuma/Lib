int n, k, mx_lvl, vis[maxn], dist[maxn], sz[maxn] ;
long long ans, f[maxn] ; 
void dfs(int v, int p) // dfs padrao pra calcular sz de comp
 
int find_cent(int v, int p, int szz){
 
    for(auto a : grafo[v]){
        if(vis[a] || a == p || 2*sz[a] <= szz) continue ;
        return find_cent(a, v, szz) ;
    }
 
    return v ;
}
 
void mk_ct(int v, int p, int type, int lvl){
 
    mx_lvl = max(mx_lvl, lvl) ;
 
    if(lvl > k) return ;
 
    if(type) f[lvl]++ ;
    else ans += f[k-lvl] ;
 
    for(auto a : grafo[v]){
        if(vis[a] || a == p) continue ;
        mk_ct(a, v, type, lvl + 1) ;
    }
 
}
 
void make_cent(int v, int p){
 
    dfs(v, p) ;
 
    int c = find_cent(v, p, sz[v]) ;
 
    vis[c] = 1 ; mx_lvl = 0 ;
    f[0] = 1 ;
 
    for(auto a : grafo[c]){
        if(vis[a] || a == p) continue ;
        mk_ct(a, c, 0, 1) ;
        mk_ct(a, c, 1, 1) ;
    }
 
    for(int i = 1 ; i <= mx_lvl ; i++) f[i] = 0 ;
 
    for(auto a : grafo[c]){
        if(vis[a] || a == p) continue ;
        make_cent(a, c) ;
    }
 
}
