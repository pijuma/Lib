// caminho que passa por todas arestas, grafo bidi 
// que direção da aresta eu usei? 
void hamil(int u, int id_e){
    deubom[u] = 1 ; 
    while(grafo[u].size()){
        auto e = grafo[u].back();
        int v = e.ff, id = e.ss;
        grafo[u].pop_back();
 
        if(vis[id]){
            continue;
        }
 
        vis[id] = 1;
        hamil(v, id);
    }
 
    if(id_e != -1){
        if(ori[id_e].ff == u){
            ans[id_e] = 1;
        }
        else{
            ans[id_e] = -1;
        }
    }   
}
 
void dfs_add(int v, int p, int id){
    vis[v] = 1 ; 
    for(auto a : g[v]){
        if(a.ff == p || vis[a.ff]) continue ; 
        dfs_add(a.ff, v, a.ss) ; 
    }
    if(p != -1){
        if(grau[v]&1){
            grafo[v].pb({p, id}); grafo[p].pb({v, id}) ; 
            grau[v]++ ; grau[p]++ ; 
        }
    }
    else{
        if(grau[v]&1) {
            cout << "N\n" ; exit(0) ; 
        }
    }
}
