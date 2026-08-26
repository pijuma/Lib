// grafo g, verts de 1 ate n
map<vi, int> mp;
int dfs_hash(int u, int p=0) {
    vi vec;

    for(int v : g[u]) {
        if(v != p) {
            int h = dfs_hash(v, u);
            vec.pb(h);
        }
    }

    sort(vec.begin(), vec.end());
    if(mp.count(vec)) return mp[vec];
    return mp[vec] = mp.size();
}

// DAQUI PRA BAIXO EH SE VOCE PRECISA COMPARAR UNROOTED
int lvl[maxn], pai[maxn];
void dfs(int u, int p=0, int l=0) {
    pai[u] = p;
    lvl[u] = l;
    for(int v : g[u])
        if(v != p) dfs(v, u, l + 1);
}

pii find_centers() {
    int rr;
    for(int k = 0; k < 2; ++k) {
        int r = k ? rr : 1;

        dfs(r);

        rr = 1;
        for(int i = 1; i <= n; ++i)
            if(lvl[i] > lvl[rr]) rr = i;

        if(!k) r = rr;
    }

    vector<int> aux;
    for(; rr; rr = pai[rr])
        aux.pb(rr);

    int sz = aux.size();
    return {aux[sz / 2], (sz%2) ? 0 : aux[sz / 2 - 1]};
}

pii hash_unrooted() {
    auto [c1, c2] = find_centers();
    int h1 = dfs_hash(c1);
    int h2 = c2 != 0 ? dfs_hash(c2) : -1;
    if(h1 > h2) swap(h1, h2);
    return {h1, h2};
}
