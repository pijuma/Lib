/*
acha max_flow 
que é igual em valor ao min_cut (arestas no min_cut limitam o fluxo max) 
com otimização "scaling algorithm" O(m^2*log(MaxC)) - rapido enough 
*/

#define pb push_back
#define pii pair<int,int> 
#define ff first 
#define ss second 

const int N = 550 ;

int MaxC ; 
int ar[N][N] ; //existe aresta de i pra j? 

struct Ford {
    struct Edge {
        int to, f, c;
    };

    int vis[N+2];
    vector<int> adj[N];
    vector<Edge> edges;
    int cur, tempo;

    Ford(){
        cur = 0 ; tempo = 1 ; 
        for(int i = 0 ; i <= N ; i++) vis[i] = 0 ; 
    }

    void addEdge(int a, int b, int cap, int rcap) {
        Edge e;// cria aresta de ida
        e.to = b; e.c = cap; e.f = 0;
        edges.pb(e);
        adj[a].pb(cur++);

        e = Edge(); // cria aresta de volta
        e.to = a; e.c = rcap; e.f = 0;
        edges.pb(e);
        adj[b].pb(cur++);
    }

    int dfs(int s, int t, int f, int tempo, int val) {
        
        if(s == t) return f; // f guarda o valor min de capacidade 
        
        vis[s] = tempo;// ja visitou nessa dfs?

        for(int e : adj[s]) {
            if(edges[e].c - edges[e].f < val) continue ; 
            if(vis[edges[e].to] < tempo and (edges[e].c - edges[e].f) > 0) {
                if(int a = dfs(edges[e].to, t, min(f, edges[e].c-edges[e].f) , tempo, val)) {
                    edges[e].f += a; // inversões das arestas
                    edges[e^1].f -= a; // add no sentido contrario e remove no atual 
                    return a;//dfs retorna o min 
                }
            }
        }
        
        return 0;

    }

    int flow(int s, int t) {

        int mflow = 0;
        
        for(int i = log2(MaxC) ; i >= 0 ; i--){
           while(int a = dfs(s, t, MaxC, tempo, (1<<i))){
                mflow += a; // a -> corte minimo do caminho atual 
                tempo++;
           }
           tempo++ ; 
        }
        
        return mflow; // fluxo maximo = qtd de camnihos de S pra T 
    
    }

    void dfs_cut(int v, int p){
        vis[v] = tempo ; 
        for(auto a : adj[v]){
            auto ed = edges[a] ;
            if(ed.to == p || vis[ed.to] == tempo) continue ;  
            if(ed.f == ed.c) continue ; 
            dfs_cut(ed.to, v) ; 
        }
    }

    void find_cut(int s, int t, int n){
       vector<pii> cut ; 
       flow(s, t) ; //monta o fluxo 
       tempo++ ; 
       dfs_cut(s, s) ; // dfs com ini =s passando so pelas arestas n esgotaram = monta uma componente  
       for(int i = 1 ; i <= n ; i++){ //add a aresta se ela nao for reversa e for de algum visitado pra um nao visitado (dividiu em 2 sets) 
            for(auto a : adj[i]){
                auto ed = edges[a] ;  
                if(vis[i] == tempo && vis[ed.to] != tempo && ar[i][ed.to] == 1){
                    cut.pb({i, ed.to}) ; 
                }
            }
       }
    }

};
