//mcmf pra pegar matching 
const int INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 1e4 + 5 ; 
 
struct Dinitz {
  struct Edge {
    int v, u, cap, flow=0, cost;
    Edge(int v, int u, int cap, int cost) : v(v), u(u), cap(cap), cost(cost) {}
  };
 
  int n, s, t;
  Dinitz(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
  }
 
  vector<Edge> edges;
  vector<vector<int>> adj;
  void add_edge(int v, int u, int cap, int cost) {
    edges.emplace_back(v, u, cap, cost);
    adj[v].push_back(size(edges)-1);
    edges.emplace_back(u, v, 0, -cost);
    adj[u].push_back(size(edges)-1);
  }
 
  vector<int> dist;
  bool spfa() {
    dist.assign(n, INF);
 
    queue<int> Q;
    vector<bool> inqueue(n, false);
 
    dist[s] = 0;
    Q.push(s);
    inqueue[s] = true;
 
    vector<int> cnt(n);
 
    while (!Q.empty()) {
      int v = Q.front(); Q.pop();
      inqueue[v] = false;
 
      for (auto eid : adj[v]) {
        auto const& e = edges[eid];
        if (e.cap - e.flow <= 0) continue;
        if (dist[e.u] > dist[e.v] + e.cost) {
          dist[e.u] = dist[e.v] + e.cost;
          if (!inqueue[e.u]) {
            Q.push(e.u);
            inqueue[e.u] = true;
          }
        }
      }
    }
 
    return dist[t] != INF;
  }
 
  int cost = 0;
  vector<int> ptr;
  int dfs(int v, int f) {
    if (v == t || f == 0) return f;
    for (auto &cid = ptr[v]; cid < size(adj[v]);) {
      auto eid = adj[v][cid];
      auto &e = edges[eid];
      cid++;
      if (e.cap - e.flow <= 0) continue;
      if (dist[e.v] + e.cost != dist[e.u]) continue;
      int newf = dfs(e.u, min(f, e.cap-e.flow));
      if (newf == 0) continue;
      e.flow += newf;
      edges[eid^1].flow -= newf;
      cost += e.cost * newf;
      return newf;
    }
    return 0;
  }
 
  int total_flow = 0;
  int flow() {
    while (spfa()) {
      ptr.assign(n, 0);
      while (int newf = dfs(s, INF))
        total_flow += newf;
    }
    return total_flow;
  }
 
  vector<pair<int,int>> recuperar_matching(int source, int sink){
    vector<pair<int,int>> resp ; 
    // ***o n que eu somo em j não é o n da struct na verdade é n/3 ****
    for(auto a : edges){
        if(a.v == sink || a.v == source) continue ; 
        if(a.u == sink || a.u == source) continue ; 
        if(a.u <= (n/3)) continue ; 
        if(a.v > (n)/3|| a.v <= 0) continue ; // /3 pq eu coloquei 3*n como n na hora de criar o dinic
        if(!a.flow) continue ; 
        resp.push_back({a.v, a.u-(n/3)}) ; 
    }
    return resp ; 
  }
 
};
 
int k[maxn][maxn] ; 
char g[maxn][maxn] ;
 
int32_t main(){
 
    int n ; cin >> n ; 
 
    Dinitz dinic((3*n), 0, (2*n)+1) ; 
 
    int sl = 0, sc = 0 ; 
 
    for(int i = 1 ; i <= n ; i++){
        int l ; cin >> l ; 
        sl += l ; 
        dinic.add_edge(0, i, l, 0) ; 
    }
 
    for(int i = 1 ; i <= n ; i++){
        int c ; cin >> c ; 
        sc += c ; 
        dinic.add_edge(i+n, (2*n) + 1,  c, 0) ; 
    }
 
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            int v ; cin >> v ;k[i][j] = v ;  
            dinic.add_edge(i, j+n, 1, inf-v) ; 
        }
    }
 
    if(sc != sl){
        cout << "-1\n" ; return 0 ; 
    }
 
    int z = dinic.flow() ; 
    
    if(z != sc){
        cout << "-1\n" ; return 0 ; 
    }
 
    auto ans = dinic.recuperar_matching(0, (2*n)+1) ; 
    int r = 0 ; 
 
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++) g[i][j] = '.' ; 
    }
 
    for(auto a : ans){
        r += k[a.first][a.second] ; 
        g[a.first][a.second] = 'X' ; 
    }
 
    cout << r << "\n" ; 
 
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++) cout << g[i][j] ; 
        cout << "\n"; 
    }
    
}
