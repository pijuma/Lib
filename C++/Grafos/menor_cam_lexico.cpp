vector<pii> adj[maxn] ; 
pii dist[maxn] = {}; 
ll resp[maxn] ; 
int foi[maxn];
ll n, m, k;

vi auxx;
int vi2[maxn];

void dfs(int u){
    auxx.push_back(u);
    for(auto [v, w]: adj[u]){
        if(vi2[v]) continue;
        if(w == 0){
            vi2[v] = 1;
            dfs(v);
        }
    }
}


void solve(){
    cin >> n >> m >> k ; 
    auxx.clear();
    rep(i, 0, n+7){
        dist[i] = {mod, mod};
        resp[i] = -1;
        adj[i].clear();
        foi[i] = 0;
        vi2[i] = 0;
    }

    for(int i = 1 ; i <= m ; i++){
        int a, b, c ; 
        cin>>a>>b>>c;
        adj[a].pb({b, c}) ; adj[b].pb({a, c}) ; 
    }

    deque<pii> q; 
    vi vis; 
    dfs(1);
    for(auto v: auxx){
        dist[v] = {0, 0};
        resp[v] = 0;
        foi[v] = 1;
        q.push_back({0, v});
    }

    
    
    while(!q.empty()){
        auto [prio, u] = q.front();
        q.pop_front();
        // cout<<"to no "<<u<<"\n";

        for(auto [v, w]: adj[u]){
            if(!foi[v] and dist[v] > make_pair(prio, w)){
                dist[v] = {prio, w};
                resp[v] = (resp[u] * k + w) % mod;
                vis.push_back(v);
            }
        }  

        if(q.empty()){
            sort(all(vis));
            vis.erase(unique(all(vis)), vis.end());

            vector<pii> cords;

            for(auto v: vis){
                cords.push_back(dist[v]);
            }
            sort(all(cords));
            cords.erase(unique(all(cords)), cords.end());
            vector<pii> prox;
            for(auto v: vis){
                foi[v] = 1;
                int prio = distance(cords.begin(), lower_bound(all(cords), dist[v]));
                prox.push_back({prio, v});
            }

            sort(all(prox));
            for(auto &x: prox) q.push_back(x);

            vis.clear();
        }
    }

    rep(i, 1, n+1) cout<<resp[i]<<" ";
    cout<<"\n";
}
