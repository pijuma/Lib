    
struct DSU{
    
    int find(int u){ return u == pai[u] ? u : find(pai[u]) ; }
    
    void join(int a, int b){
    
        a = find(a), b = find(b) ; 
    
        if(a == b){
            last.push_back({-1,-1}), comp.push_back(-1) ; 
            return ; 
        } 
    
        if(sz[a] > sz[b]) swap(a, b) ; // b smp vira pai 
    
        last.push_back({b, a}), comp.push_back(qtd) ; //add a no b 
        pai[a] = b ; 
        sz[b] += sz[a] ; 
        qtd-- ; 
    
    }
    
    void rollback(){
        
        int u = last.back().first, v = last.back().second, qtd_comp = comp.back() ; 
        
        if(u == -1 && v == -1 && qtd_comp == -1){
            last.pop_back(), comp.pop_back() ; 
            return ; 
        }
    
        qtd = qtd_comp ;
        pai[v] = v ; 
        sz[u] -= sz[v] ; 
        last.pop_back(), comp.pop_back() ; 
    
    }
    
    int qtd_comp(){ return qtd ; }
    
}dsu ; 
