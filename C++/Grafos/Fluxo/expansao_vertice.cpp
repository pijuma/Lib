/*
pega o grid 
p cada canto conecta os adjs q ele tem 
o source liga com capacidade 1 pra cada ponto q tem 
banco 
e os kras adjs a saidas ligam p sink c capacidade 1 tbm 
*/

int32_t main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 

    int t ; cin >> t ;
    
    while(t--){ 

        Dinic dinic ; 

        cin >> n >> m >> b ;

        ct = 0 ; numb.clear() ;  

        for(int i = n ; i >= 1 ; i--){
            for(int j = 1 ; j <= m ; j++){
                numb[{i, j}] = ++ct ; 
                who[ct] = {i, j} ; 
            }
        }

        vector<int> bnks ; set<int> ends; 

        for(int i = 1 ; i <= b ; i++){
            int x, y ; cin >> x >> y ; 
            int val = numb[{x, y}] ; 
            bnks.pb(val) ; 
            vis[val] = 1 ; 
        }

        int add = n*m ; 

        int S = 0, T = ((2*n*m)+(add)) + 2 ; 

        for(auto a : bnks){
            dinic.addEdge(S, a+add, 1, 0) ;
        }

        set<int> vals ; 

        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m ; j++){
                for(int k = 0 ; k < 4 ; k++){
                    int ti = i + dx[k], tj = j + dy[k] ; 
                    if(!valid(ti, tj)){
                        ends.insert(numb[{i, j}]) ; 
                        //dinic.addEdge(numb[{i, j}], T, 1, 0) ;
                    }
                    else{
                        if(!vis[numb[{ti, tj}]]){
                            // a -> b 
                            // a'->a->b'->b 
                            vals.insert(numb[{ti, tj}]) ; vals.insert(numb[{i, j}]) ; 
                            dinic.addEdge(numb[{i, j}], numb[{ti, tj}]+add, 1, 0) ; 
                        } 
                    }
                }
            }
        }

        for(auto a : vals) dinic.addEdge(a+add, a, 1, 0) ; 
        for(auto a : ends) dinic.addEdge(a+add, T, 1, 0) ; 

        for(auto a : bnks) vis[a] = 0 ; 

        int flw = dinic.flow(S, T) ; 

        if(flw == b) cout << "possible\n" ; 
        else cout << "not possible\n" ; 

    }

}
