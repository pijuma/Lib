vector<int> cnt, path;

void dfs(int u, int k, int d=0, int p=-1) {
    //if(d > k+3) return ; -> tentar ignorar se ficar muito maior que k 
    path.push_back(d);
    for (int v : g[u]) if (v != p and !rem[v]) dfs(v, k, d+1, u);
}

int dfs_sz(int u, int p=-1) {
    sz[u] = 1;
    for (int v : g[u]) if (v != p and !rem[v]) sz[u] += dfs_sz(v, u);
    return sz[u];
}

int centroid(int u, int p, int size) {
    for (int v : g[u]) if (v != p and !rem[v] and 2 * sz[v] > size)
        return centroid(v, u, size);
    return u;
}

ll decomp(int u, int k) {
    int c = centroid(u, u, dfs_sz(u));
    rem[c] = true;

    ll ans = 0;

    cnt.resize(sz[u]);
    fill(cnt.begin(), cnt.end(), 0);

    cnt[0] = 1;
    for (int v : g[c]) if (!rem[v]) {
        path.clear();
        dfs(v, k);
        // d1 + d2 + 1 == k
        //passo por todos add na resp dps incluindo ele 
        for (int d : path) if (0 <= k-d-1 and k-d-1 < sz[u])
            ans += cnt[k-d-1];
        for (int d : path) cnt[d+1]++;
    }

    for (int v : g[c]) if (!rem[v]) ans += decomp(v, k);
    return ans;
}
