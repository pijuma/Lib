
const int LLINF = 1e18 ; 
const int N = 505;
 
int n, m, ar[N][N] ; 
int lim, grau[N] ;
map<pair<int,int>, int> usado ;
vector<int> cam ; 

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
        memset(lvl, -1, sizeof(lvl)) ;  
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

} ;
 
int32_t main(){

    Dinic dinic ; dinic.reset_flow() ;
    
    //conectar do source = 0 pra tds linhas 
    // das colunas pro sink = 2n + 1 

    for(int i = 1 ; i <= n ; i++){
        dinic.addEdge(0, i, 1, 0) ; 
        dinic.addEdge(i+n, 2*n + 1, 1, 0) ; 
    }

    //tem que ser bipartido
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            char a ; cin >> a ; 
            if(a == 'o'){
                dinic.addEdge(i, j+n, LLINF, 0) ;
            }
        }
    }
   //n - c = qtd de caminhos, sao as arestas n usadas
    cout << n - dinic.flow(0, 2*n + 1) << "\n" ; 
    
}
