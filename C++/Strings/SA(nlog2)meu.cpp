#include <bits/stdc++.h>
using namespace std;

/*
Menor shift ciclico -> comeca em p[0]
checar se tem substring s em um texto t -> faz SA em t e busca binaria (caderno rosa)
checar se duas substrings são iguais -> função compare + sparse table
*/

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
       sort(strs.begin(), strs.end()) ;
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

vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    return sorted_shifts;
}
