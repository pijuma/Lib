struct KMP{
    
    vector<int> phi ;

    vector<int> prefix_kmp(string s){
        
        phi.resize(s.size()+1, 0) ;

        for(int i = 1 ; i < s.size() ; i++){
            
            int &j = phi[i] ; 
            j = phi[i-1] ; 

            //vou pulando pelos sufixos (pra pegar os prefs)
            while(j > 0 && s[i] != s[j]) j = phi[j-1] ; 

            if(s[i] == s[j]) j++ ; 

        }

        return phi ; 

    }

} ;

/*
quero pegar todos os sufixos que batem com prefixos -> vou andando no sufixo do prefixo pelo phi
preciso saber quantas vezes cada um apareceu:
freq[res[i-1]] += (freq[i]+1) um prefixo/sufixo menor ta incluso num maior que vem antes dele 
*/

int main(){

    string s ; cin >> s ; 
    
    KMP A ; 

    vector<int> res = A.prefix_kmp(s) ; 

    vector<int> pos ; 

    for(int i = s.size()-1 ; i >= 0 ; i = res[i] - 1){//pega o maior suf do pref q peguei
        pos.pb(i+1) ; 
    } 

    cout  << pos.size() << "\n" ;

    sort(pos.begin(), pos.end()) ; 

    vector<int> freq(s.size()+2, 0) ; 

    freq[s.size()] = 1 ; 

    for(int i = s.size() ; i >= 1 ; i--){
        freq[res[i-1]] += (freq[i]+1)  ;
    }
    
    for(auto a : pos){
        cout << a << " " << freq[a] << "\n" ; 
    }

}
