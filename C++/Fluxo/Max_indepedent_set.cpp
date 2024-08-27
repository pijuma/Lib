/*
passa por cada celula 
olha semre acima e esq 
ve se ambas sao pretas se sim 
criamos o vertice ++ct
guardamos a linha e coluna da anterior e atual 
guarda o anterior e proximo qual id do vertice tb 
p cada vertice do grafo 
olhamos o kra que esta acima e a esquerda 
e vemos se forma um L 
n forma se todos tao na mesma linha ou coluna 
*/

ll lim ; 

const int inf = 1e9 + 5 ; 
const int N = (800*800) ; 
const int maxn = (800*800) ; 
const int LLINF = 1e9 ; 
const int maxx = 210 ; 

struct Dinic {
 
    struct Edge{
        int from, to; ll flow, cap;
    };
 
    vector<Edge> edge;
 
    vector<int> g[N];
    int ne = 0;
    int lvl[N], vis[N], pass;
    int qu[N], px[N], qt;
 
    ll run(int s, int sink, ll minE) {
        if(s == sink) return minE;
 
        ll ans = 0;
 
        for(; px[s] < (int)g[s].size(); px[s]++) {
            int e = g[s][ px[s] ];
            auto &v = edge[e], &rev = edge[e^1];
            if(lvl[v.to] != lvl[s]+1 || v.flow >= v.cap)
                continue;           
            if(v.cap - v.flow < lim) continue ; 
            ll tmp = run(v.to, sink,min(minE, v.cap-v.flow));
            v.flow += tmp, rev.flow -= tmp;
            ans += tmp, minE -= tmp;
            if(minE == 0) break;
        }
        return ans;
    }
    bool bfs(int source, int sink) {
        qt = 0;
        qu[qt++] = source;
        lvl[source] = 1;
        vis[source] = ++pass;
        for(int i = 0; i < qt; i++) {
            int u = qu[i];
            px[u] = 0;
            if(u == sink) return true;
            for(auto& ed : g[u]) {
                auto v = edge[ed];
                if(v.flow >= v.cap || vis[v.to] == pass)
                    continue; 
                if(v.cap - v.flow < lim) continue ; 
                vis[v.to] = pass;
                lvl[v.to] = lvl[u]+1;
                qu[qt++] = v.to;
            }
        }
        return false;
    }

    ll flow(int source, int sink) {
        reset_flow();
        ll ans = 0;
        for(lim = (1LL << 62); lim >= 1; lim /= 2){
            while(bfs(source, sink))
            ans += run(source, sink, LLINF);
        }
        return ans;
    }

    void addEdge(int u, int v, ll c, ll rc) {
        Edge e = {u, v, 0, c};
        edge.pb(e);
        g[u].push_back(ne++);
 
        e = {v, u, 0, rc};
        edge.pb(e);
        g[v].push_back(ne++);
    }
    void reset_flow() {
        for(int i = 0; i < ne; i++)
            edge[i].flow = 0;
        memset(lvl, 0, sizeof(lvl));
        memset(vis, 0, sizeof(vis));
        memset(qu, 0, sizeof(qu));
        memset(px, 0, sizeof(px));
        qt = 0; pass = 0;
    }

 vector<pair<int,int>> recuperar_matching(int source, int sink){
        vector<pair<int,int>> resp ; 
        for(auto a : edge){
            if(a.from == sink || a.from == source) continue ;
            if(a.to == sink || a.to == source) continue ; 
            if(a.to <= n) continue ;
            if(a.from > n || a.from <= 0) continue ;  
            if(!a.flow) continue ; 
            resp.push_back({a.from, a.to-n}) ; 
        }
        return resp ; 
    }


    void matching(int source, int sink, int m){
        for(int i = 1 ; i <= m ; i++){ // meninas
            addEdge(source, i+n, 1, 0) ; 
        }
    
        for(int i = 1 ; i <= n ; i++){ // meninos 
            addEdge(i, sink, 1, 0) ; 
        }
    
        for(int i = 1 ; i <= m ; i++){
            int b, g ; cin >> b >> g ; 
            //cout << "aresta " << g+n << " " << b << "\n" ; 
            addEdge(g+n, b, 1, 0) ;
        }
        
        vector<pair<int,int>> ans = recuperar_matching(source, sink) ;

    }



} ;

Dinic dinic ;
set<pii> edges ; 

void create(int id, pii l, pii c){
    if(who.find({l, c}) == who.end()) return ; 
    int id2 = who[{l, c}] ; 
    if(hor[id]) swap(id, id2) ; 
    if(edges.find({id, id2}) != edges.end()) return ;
    //cout << "aresta\n" ; 
    //imp(id) ; imp(id2) ; 
    //cout << "\n" ;  
    edges.insert({id, id2}) ; 
    dinic.addEdge(id, id2, 1, 0) ;
}

int32_t main(){

    int bb = 0 ; 

    cin >> n >> m ; 


    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            cin >> g[i][j] ;
            if(g[i][j] == '#') bb++ ; 
        }
    }

    //criar vertices horizontais - em q linha ele ta 
    for(int i = 1 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){// entre quais colunas (j, j+1) 
            pii lin, col ; 
            lin = {i, i} ; col = {j, j+1} ; 
            //vertice existe se tiver preto em cima e embaixo 
            if(g[i+1][j+1] == '#' && g[i][j+1] == '#'){
                who[{lin, col}] = ++ct ; 
                //cout << "criei hor\n" ; 
                //cout << "linha " << i << " " << j << " " << j+1 << "\n" ; 
                adjs[ct] = {lin, col} ; 
                hor[ct] = 1 ; 
            }
        }
    }

    //criar vertices verticais - em que coluna ele ta 
    for(int j = 1 ; j < m ; j++){
        for(int i = 0 ; i < n ; i++){//esta entre a linha (i, i+1)
            pii lin, col ; 
            lin = {i, i+1} ; col = {j, j} ;
            if(g[i+1][j] == '#' && g[i+1][j+1] == '#'){
                //cout << "vertical\n" ; 
                //cout << "coluna " << j << " " << i << " " << i + 1 << "\n"; 
                who[{lin, col}] = ++ct ; 
                adjs[ct] = {lin, col} ; 
            } 
        }
    }

    // source sink 
    int S = 0, T = ct+1 ; 

    //montar grafo 

    for(int i = 1 ; i <= ct ; i++){
        if(hor[i]){
            int linha, coluna_ini, coluna_fim ; 
            linha = adjs[i].ff.ff ; 
            coluna_ini = adjs[i].ss.ff ; coluna_fim = adjs[i].ss.ss ; 
            pii lin = {-1, -1}, col = {-1, -1} ; 
            //procurar os verticais 
            col = {coluna_ini, coluna_ini} ;
            lin = {linha-1, linha} ;
            create(i, lin, col) ;
            lin = {linha, linha+1} ; 
            create(i, lin, col) ; 
            col = {coluna_fim, coluna_fim} ; 
            create(i, lin, col) ; 
            lin = {linha-1, linha} ; 
            create(i, lin, col) ;    
        }
        else{//vertical ligando c horizontal
            int linha_ini, linha_fim, coluna ; 
            coluna = adjs[i].ss.ff ; 
            linha_ini = adjs[i].ff.ff, linha_fim = adjs[i].ff.ss ;
            pii lin = {-1, -1}, col = {-1, -1} ; 
            lin = {linha_ini, linha_ini} ; 
            col = {coluna-1, coluna} ; 
            create(i, lin, col) ;
            col = {coluna, coluna+1} ; 
            create(i, lin, col) ;
            lin = {linha_fim, linha_fim} ; 
            create(i, lin, col) ; 
            col = {coluna-1, coluna} ; 
            create(i, lin, col) ;  
        }
    }

    for(int i = 1 ; i <= ct ; i++){
        if(hor[i]) dinic.addEdge(i, T, 1, 0) ; 
        else dinic.addEdge(S, i, 1, 0) ;
    }

    //cout << ct << " " << bb << "\n" ; 
    cout << bb - (ct-dinic.flow(S, T)) << "\n" ; 

}
