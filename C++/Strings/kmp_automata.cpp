struct KMP{
    
    vector<int> phi ;

    int next(int c){
    
        int i = s.size(); 
        phi.pb(0) ;
        s.push_back(c) ; 

        if(i == 0) return 0 ; 

        int &j = phi[i] ; 
        j = phi[i-1] ; 

        //vou pulando pelos sufixos (pra pegar os prefs)
        while(j > 0 && s[i] != s[j]) j = phi[j-1] ; 

        if(s[i] == s[j]) j++ ;  

        return phi[i] ; 

    }

    void erase(){
        phi.pop_back() ; 
        s.pop_back() ;
    }

    void see(){
        for(auto a : phi) cout << a << " " ; 
        cout << "\n" ; 
    }
} ;
/*
Na main:  KMP nome ;
nome.erase() etc 
*/
