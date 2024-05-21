/*
acha max_flow 
que é igual em valor ao min_cut 
com otimização "scaling algorithm" O(m^2*log(MaxC)) - rapido enough 
Cuidado: quando for grafo denso ou bipartido -> usar Dinic (se constraints forem paias)
*/
#define pb push_back

const int N = 550 ;//qtd vertices

int MaxC ; //maior capacidade de aresta dada

struct Ford {
    struct Edge {
        int to, f, c;
    };

    int vis[N];
    vector<int> adj[N];
    vector<Edge> edges;
    int cur = 0;

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

        int mflow = 0, tempo = 1;
        
        for(int i = log2(MaxC) ; i >= 0 ; i--){
           while(int a = dfs(s, t, MaxC, tempo, (1<<i))){
                mflow += a; // a -> corte minimo do caminho atual 
                tempo++;
           }
           tempo++ ; 
        }
        
        return mflow; // fluxo maximo = qtd de camnihos de S pra T 
    
    }

};
