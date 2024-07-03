/*
given nodes whithout incoming edges, let those be S 
dado qualquer iteração do 1o passo 
se S tiver mais de um nó, pegue qualquer um 
qualquer maior S possivel no 1o passo pra dar bom? 
queremos a antichain (set de nós tal que nao existe caminho entre um vertice e outro)
= min general path cover (se a alcança b coloca aresta de a pra b)
faz max matching 
liga pra um S e T 
nesee problema devemos ignorar os vertices que fazem parte de um ciclo
*/

const int N = 500*500*2 ; 
const int maxn = 500*500*2 ; 
const int LLINF = 1e9 ; 

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

} ;

void dfs(int v, int p){
    vis[v] = 1 ; 
    for(auto a : grafo[v]){
        if(a == p || vis[a]) continue ; 
        dfs(a, v) ; 
    }
}

void ord_topo(){

    queue<int> fila ; 

    for(int i = 0 ; i < n ; i++) if(!grau[i]) fila.push(i) ; 

    while(!fila.empty()){
        int at = fila.front() ; fila.pop() ; 
        for(auto a : grafo[at]){
            if(!(--grau[a])) fila.push(a) ; 
        }
    }

}

int main(){

    cin >> n >> m ; 

    Dinic dinic ; 

    for(int i = 1 ; i <= m ; i++){
        int a, b ; cin >> a >> b ; 
        grafo[a].push_back(b) ; 
        grau[b]++ ; 
    }

    vector<int> indg ; 

    ord_topo() ; 

    for(int i = 0 ; i < n ; i++) if(grau[i]) indg.push_back(i) ; //retirar ciclos 

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++) vis[j] = 0 ; 
        dfs(i, i) ; 
        for(int j = 0; j < n ; j++){
            if(!vis[j]) continue ; 
            if(i == j) continue ; 
            if(grau[i]) continue ; // coloca so se ambos forem validos (ciclo fora )
            if(grau[j]) continue ; 
            //cout << "aresta de " << i << " para " << j << "\n" ; 
            dinic.addEdge(i, j+n, 1, 0)  ; 
        }
    }

    //S = 2n T = 2n+1 
    //montando max matching 

    for(int i = 0 ; i < n ; i++){
        dinic.addEdge(2*n, i, 1, 0); 
        dinic.addEdge(i+n, 2*n+1, 1, 0) ; 
    }

    // indg nao pode estar na resposta ss
    cout << n -  dinic.flow(2*n, 2*n+1)  - (int)indg.size() << "\n" ;  
}
