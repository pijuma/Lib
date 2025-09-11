/*
achar quantas subsequencias diferentes temos 
preciso fazer com os valores sejam 0 index 
e faço suffix array em cima do vector<int> e nao da string 
*/
void radix(vector<pair<pair<int, int>, int>> &vec){

    //ordena pelo segundo, conta quantos valores de cada
    //separa um vetor pra colocar todo mundo ordenado 

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

vector<int> sort_cyclic_shifts(vector<int> s) {
    
    n++ ; 

    vector<int> p(n), c(n) ; // p mantem a ordem e c a classe do kra i 
    vector<pair<int,int>> a(n) ;
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
   
   n-- ; 

   return p ; 
    
}

//se não quiser considerar o sufixo vazio, remover o 1o elemento
vector<int> suffix_array_construction(vector<int> v) {
    v.pb(0) ; 
    vector<int> sorted_shifts = sort_cyclic_shifts(v); 
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

vector<int> v ; 

vector<int> compute_lcp(vector<int> &sa){

    int k = 0 ; 
    vector<int> lcp(n, 0) ;
    vector<int> where(n, 0) ; 

    for(int i = 0 ; i < n ; i++) where[sa[i]] = i ; 

    for(int i = 0 ; i < n ; i++){
        int psa = where[i] ; //onde eu to no sa 
        if(psa == 0){
            k = 0 ; continue ; 
        }
        int pant = sa[psa-1] ; //qual pos ta antes de mim  
        while(i + k < n && pant + k < n && v[i+k] == v[pant+k]){
            k++ ;  
        }
        lcp[psa] = k ; //lcp da posição ordenada  
        if(k) k-- ; //pode reduzir uma unidade pro prox 

    }
    return lcp ; 
}

const int maxn = 1e5 + 5 ; 

int minesq[maxn], mindir[maxn] ; 

int32_t main(){

    cin >> n ; 

    for(int i = 1 ; i <= n ; i++){
        int a ; cin >> a ; 
        v.pb(a); 
    }

    vector<int> ans = suffix_array_construction(v) ; 
    vector<int> lcp = compute_lcp(ans) ;

    int tot = n*n; //todas substrings possiveis 
    //quantas batem? 
    //pra cada lcp preciso saber quantas vezes ele é valido 
    //qual o primeiro menor antes dele e depois? 

    minesq[0] = -1 ;

    for(int i = 1 ; i < n ; i++){
        minesq[i] = i-1 ; 
        while(minesq[i] != -1 && lcp[minesq[i]] >= lcp[i]) minesq[i] = minesq[minesq[i]] ; 
    }

    mindir[n-1] = n ; 

    for(int i = n-2 ; i >= 0 ; i--){
        mindir[i] = i+1 ; 
        while(mindir[i] != n && lcp[mindir[i]] > lcp[i]) mindir[i] = mindir[mindir[i]] ; 
    }

    int same = n*(n+1)/2 ; //(i, i)
    int pontas = 0 ; 

    for(int i = 1 ; i < lcp.size() ; i++){
        int sz = lcp[i] ; 
        //em quais eu sou resp? 
        int l = minesq[i], r = mindir[i] ; 
        if(l==-1) l++ ;
        r-- ; 
        if(l > r) continue 
        int qtdl = (i-l), qtdr = (r-i+1) ;
        //de l até i * de i + 1 até r 
        pontas += (qtdl*qtdr*sz)  ; 
    }

    int total = same + 2*pontas ; 

    int gcdd = __gcd(total, tot) ; 
    total /= gcdd ; tot /= gcdd ; 

    cout << total << "/" << tot << "\n" ; 
}
