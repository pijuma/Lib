#define ff first 
#define ss second 
#define pii pair<int,int> 

/*
O(nlogn) -> pode otimizar um pouco mais 
deixando a ordenação pelo 2o termo ja automatica (cp tá assim) 
Menor shift ciclico -> comeca em p[0]
checar se tem substring s em um texto t -> faz SA em t e busca binaria (caderno rosa)
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
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

int main(){
    
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 

    string s ; cin >> s ; 
    vector<int> ans = suffix_array_construction(s) ;
    
    for(auto a : ans) cout << a << " " ;
    cout << "\n" ;
    
}
