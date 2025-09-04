/*
Precisava checar quais vertices eu alcanço 
mas nao posso fzr com a dp padrao "reachable nodes" pq 
nao tem memoria pro bitset -> faz dfs iterativa 
*/

//i -> i+64 quais me alcançam quais eu alcanço? 
for(int l = 0 ; l < n ; l += 64){
    int r = min(n, l+64) ; 
    for(int i = l ; i < r ; i++) mask[i] = (1ull<<(i-l)) ;
    for(auto a : ar){
        mask[a.ff] |= mask[a.ss] ; 
    } 
    for(int j = 0 ; j < n ; j++) {
        ans -= __builtin_popcountll(mask[j]) ; 
        mask[j] = 0 ; 
    }
}
