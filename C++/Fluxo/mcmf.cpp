//mcmf pra pegar matching 
// cuidado com n = 1 se colocar 3*n como max e 2*n + 1 pode dar 2n+1 = 3n etc
//do source pro sink etc = usar custo 1 
// se quiser fzr max cost pode fzr inf - c assim estamos tentando maximizar o valor
const int INF = 0x3f3f3f3f3f3f3f3f;

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

  int recuperar_uso(){
    int tot = 0 ;
    for(auto a : edges){
        if(!a.flow) continue ; 
        int gasto = a.flow*a.cost ;
        tot += gasto ;  
    } 
    return tot/2 ; 
  }


};
