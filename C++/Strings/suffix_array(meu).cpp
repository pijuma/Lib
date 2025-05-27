/*
O(nlogn)
Menor shift ciclico -> comeca em p[0]
checar se duas substrings são iguais -> função compare + sparse table
*/
void radix(vector<pair<pair<int, int>, int>> &vec){

    //ordena pelo segundo, conta quantos valores de cada
    //separa um vetor pra colocar todo mundo ordenado 

    int n = vec.size() ; 
    vector<int> cnt(n+1, 0) ; 

    for(auto a : vec) cnt[a.ff.ss]++ ; 

    vector<pair<pii,int>> ord_2(n) ; 
    vector<int> pos(n+1) ; //pra cada bucket qual 1a pos livre? 

    pos[0] = 0 ; //bucket 0 ta livre em 0 

    for(int i = 1 ; i < n ; i++){
        pos[i] = pos[i-1] + cnt[i-1] ; 
    }

    for(auto a : vec){//colocar no bucket certo 
        int bucket = a.ff.ss ; 
        ord_2[pos[bucket]] = a ; 
        pos[bucket]++ ; 
    }

    vec = ord_2 ; //vetor ordenado pelo 2o valor
    
    //usa o valor ordenado pelo 2o e ordena pro 1o 
    //sem perder a ordem que temos 

    for(int i = 0 ; i < n ; i++) cnt[i] = 0 ; 

    for(auto a : vec) cnt[a.ff.ff]++ ; 
    pos[0] = 0 ; 

    for(int i = 1 ; i < n ; i++) pos[i] = pos[i-1] + cnt[i-1] ; 

    for(auto a : vec){
        int buck = a.ff.ff ; 
        ord_2[pos[buck]] = a ; 
        pos[buck]++ ; 
    }

    vec = ord_2 ; 

}

vector<int> sort_cyclic_shifts(string const &s) {
    int n = s.size();
   
    vector<int> p(n), c(n) ; // p mantem a ordem e c a classe do kra i 
    vector<pair<char,int>> a(n) ;
    for(int i = 0 ; i < n ; i++) a[i] = {s[i], i} ; 
    sort(a.begin(), a.end()) ;
    for(int i = 0 ; i < n ; i++) p[i] = a[i].second ; //q id ta é o ith menor
    
    c[p[0]] = 0 ; //1a classe 
    for(int i = 1 ; i < n ; i++){//como ta ordenado se estiverem juntos tem a mesma classe 
        c[p[i]] = c[p[i-1]];
        if(a[i].first != a[i-1].first) c[p[i]]++ ;
    }
    //classes e ordem incialmente definidas 
    // se fizer em nlog2 -> simplesmente cria o vector e ordena 
   for(int k = 0 ; (1<<k) < n ; k++){
       vector<pair<pair<int, int>, int>> strs ; 
       for(int i = 0 ; i < n ; i++) strs.push_back({{c[i], c[(i+(1<<k))%n]}, i}) ; 
       // qual classe da 1a metade e da 2a metade 
       // se a classe eh menor ent ela veio antes na ordenação anterior 
       radix(strs) ; // com isso nlog 
       //recriar o p e o c 
       for(int i = 0 ; i < n ; i++) p[i] = strs[i].second ; 
       c[p[0]] = 0 ; 
       for(int i = 1 ; i < n ; i++){
           c[p[i]] = c[p[i-1]] ;
           if(strs[i].first != strs[i-1].first) c[p[i]]++ ; 
       }
   } 
   
   return p ; 
    
}

//se não quiser considerar o sufixo vazio, remover o 1o elemento
vector<int> suffix_array_construction(string s) {
    s += "#";
    vector<int> sorted_shifts = sort_cyclic_shifts(s); 
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}


string s ; 

int check(int pos, string p){
    int n = s.size() ; 
    for(int i = 0 ; i < p.size() ; i++){
        if(i + pos >= n) return 2 ; //terminou o sufixo
        char a = s[(i+pos)], b = p[i]; 
        if(a == '$') return 2 ; 
        if(a == b) continue ; 
        if(a < b) return 2 ;
        return -1 ; 
    }
    return 1 ; 
}

void sub(vector<int> &sa, string p){//p é substring em sa? 
    
    int ini = 0, fim = sa.size() - 1, mid, best = -1 ; 

    while(ini <= fim){        
        mid = (ini + fim)>>1 ;  
        int c = check(sa[mid], p) ; 

        if(c == 1){ // é sub 
            best = mid ;  fim = mid - 1 ; 
        }
        else if(c < 0){ //p menor que sa 
            fim = mid - 1 ; 
        }
        else ini = mid + 1 ; 

    }

    if(best == -1) {cout << "0\n" ; return ; }

    ini = best, fim = sa.size()-1 ; int best2 = best ; 

    while(ini <= fim){
        mid = (ini + fim)>>1 ; 
        int c = check(sa[mid], p) ; 
        if(c == 1){
            best2 = mid, ini = mid + 1 ; 
        }
        else if(c < 0) fim = mid - 1 ; 
        else ini = mid + 1 ; 
    }
    cout << best2-best+1 << "\n" ; 

}

vector<int> compute_lcp(vector<int> &sa){

    int n = s.size() ; int k = 0 ; 
    vector<int> lcp(n, 0) ;
    vector<int> where(n, 0) ; 

    for(int i = 0 ; i < n ; i++) where[sa[i]] = i ; 

    for(int i = 0 ; i < n ; i++){
        int psa = where[i] ; //onde eu to no sa 
        if(psa == 0){
            k = 0 ; continue ; 
        }
        int pant = sa[psa-1] ; //qual pos ta antes de mim  
        while(i + k < n && pant + k < n && s[i+k] == s[pant+k]){
            k++ ;  
        }
        lcp[psa] = k ; //lcp da posição ordenada  
        if(k) k-- ; //pode reduzir uma unidade pro prox 

    }
    return lcp ; 
}

int32_t main(){

    string s1, s2 ; cin >> s1 >> s2 ; 

    s = s1 + '$' + s2 ; 

    vector<int> ans = suffix_array_construction(s) ; 

    vector<int> lcp = compute_lcp(ans) ; 

    int corte = s1.size() ; 
    int mx = 0 ; int id = -1 ; 

    for(int i = 1 ; i < ans.size() ; i++){
        int j = ans[i], k = ans[i-1] ; 
        if(j >= corte && k >= corte) continue ; 
        if(j < corte && k < corte) continue ; 
        if(lcp[i] > mx){
            mx = lcp[i] ; 
            id = j ;
        }
    }

    for(int i = id ; i < id + mx ; i++) cout << s[i] ; 
    cout << "\n" ; 

}
