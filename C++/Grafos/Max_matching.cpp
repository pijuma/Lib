// O(V^2E) 
/*acha fluxo máximo
u: O nó de origem da aresta.
v: O nó de destino da aresta.
c: A capacidade da aresta principal que vai de u para v.
rc: A capacidade da aresta reversa que vai de v para u.
s: no de origem 
sink: no destino 
cut: acha mincut -> menor conjunto de arestas que precisamos tirar para desconectar a fonte do destino -> funciona pra se tiver peso 
ele pega a qtd q minimiza a soma 
*/
    
#include<bits/stdc++.h>
#define pb push_back 
#define int long long
#define ll long long
using namespace std ;
 
const int LLINF = 1e18 ; 
const int N = 505;
 
int n, m, ar[N][N] ; 
int lim ;
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

        cout << flow(source, sink) << "\n" ; 
        vector<pair<int,int>> ans = recuperar_matching(source, sink) ;

    }



} ;
