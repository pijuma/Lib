#include<bits/stdc++.h>
using namespace std ; 

const int maxn = 1e6 + 65 ; 

// palindromo par centrado em i se i e i-1 são centros!!!
vector<int> manacher_odd(string s){//calcular pra impar

    int n = s.size() ; 
    vector<int> p(n+2) ; //pi = qtd pal centrados em i  

    s = '$' + s + '^' ;
    int l  = 1, r = 1 ; 

    for(int i = 1 ; i <= n ; i++){
        p[i] = max(0, min(r-i, p[l+(r-i)])) ; // faz parte do l, r dado? 
        //se n fizer r-i vai dar negativo e ele vai guardar 0 
        while(s[i-p[i]] == s[i+p[i]]){ //algoritmo trivial (n^2)
            p[i]++ ; 
        }
        if(i + p[i] > r){
            l = i-p[i] ; r = i+p[i] ; //arrumando os limites  
        }
    }

    return vector<int> (begin(p) + 1, end(p) - 1) ; //n passar 1a e ultima pos (caracteres add)

}

int id, mx ; 

//n qro lidar com caso par
vector<int> manacher(string s){

    string t ; 
    for(auto a : s){
        t += string("#") + a ; 
    }

    t += string("#") ; 

    auto res = manacher_odd(t) ; //transformar td em palindromo impar 

    vector<int> dpar(s.size()+2, 0), dimp(s.size()+2, 0) ; 
    //resi -> qts palindromos impares tenho centrado em i 

    for(int i = 0 ; i < s.size() ; i++){
        //tamanho de fato do valor q tenho centrado em i 
        int sz_neww_par = (2*res[2*i]-1) ;
        dpar[i] = (sz_neww_par - 1)/2 ; //max pal par em i
        int sz_neww_imp = (2*res[(2*i)+1]-1) ;
        dimp[i] = sz_neww_imp/2 ; //max pal impar em i 
    }

    //qts palindromos centrados em i? 
    //par -> tam k -> k/2 palindromos centrados ali 
    //impar -> tam k -> (k+1)/2 palindromos centrados ali 

    for(int i = 0 ; i < s.size() ; i++){
        if(mx < dpar[i]){
            mx = dpar[i] ; id = i ; 
        }
        if(mx < dimp[i]){
            mx = dimp[i] ; id = i ; 
        }
    }

    return res ; 

}

int main(){

    string s ; cin >> s ; 

    manacher(s) ; 

    int beg = id - (mx/2), end = id + (mx/2) ; 

    if(mx%2 == 0) end-- ; 
    
    for(int i = beg ; i <= end ; i++) cout << s[i] ; 
    cout << "\n" ; 

}
