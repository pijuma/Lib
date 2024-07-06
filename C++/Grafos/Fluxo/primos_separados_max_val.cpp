/*
ideia de 2sat mas escolhendo conjunto maximo = normalmente fluxo 
nao pode colocar dois cartões tal que a soma da primo juntos 
nao pode ter caminho (soma primo) 
min cut 
grafo bipartido (par vs impar)
dentre um par poibrido iremos colocar o que da mais valor pra gente
e que podemos colocar ent faz o fluxo 
colocando o valor do par pro source sendo o valor q ele da e
o valor entre par e impar como inf 
e o valor entre impar sink como o valor que o impar da 
assim iremos "filtrar" quais iremos tirar
pegando o mincut(max flow) desse grafo, sao todos
que nao podemos colocar juntos 
*/

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

struct A{
    int magic, numb, lvl ; 
} ;

int primo[maxn] ;
A kra[maxn] ; 

void crivo(){

    for(int i = 2 ; i < maxn ; i++){
        if(primo[i] == -1){
            primo[i] = 1 ; 
            for(int j = i + i ; j < maxn ; j += i) primo[j] = 0 ; 
        }
    }

}

bool cmp(A a, A b){ return a.lvl < b.lvl ; }

bool check(int mid){

    Dinic dinic ;

    vector<A> ops ; 

    for(int i = 1 ; i <= n ; i++) if(kra[i].lvl <= mid) ops.push_back(kra[i]) ; 

    int ans = 0 ; 

    for(auto a : ops) ans += a.magic ; 

    for(int i = 1 ; i <= n ; i++){
        if(kra[i].lvl > mid) continue ; 
        dinic.addEdge(0, i, kra[i].magic, 0) ; 
        dinic.addEdge(i+n, 2*n+1, kra[i].magic, 0) ; 
        for(int j = 1 ; j <= n ; j++){
            if(i == j) continue ; 
            if(!primo[kra[i].numb + kra[j].numb]) continue ; 
            dinic.addEdge(i, j+n, inf, 0) ; 
        }
    }

    ans -= (dinic.flow(0, 2*n+1))/2 ; 

    return ans >= k ; 

}

int bb(){

    int ini = 1, fim = inf, mid, best = inf ; 

    while(ini <= fim){
        mid = (ini + fim)>>1 ; 
        if(check(mid)) fim = mid - 1, best = mid ; 
        else ini = mid + 1 ; 
    }

    return best ; 

}

int32_t main(){

    cin >> n >> k ; 

    for(int i = 2 ; i < maxn ; i++) primo[i] = -1 ; 

    crivo() ; 

    for(int i = 1 ; i <= n ; i++){
        int p, c, l ; cin >> p >> c >> l ; 
        kra[i] = {p, c, l} ; 
    }

    sort(kra + 1, kra + 1 + n, cmp) ; 

    int val = bb() ; 

}
