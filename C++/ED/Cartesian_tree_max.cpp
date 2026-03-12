void create_cartesian(){

	for(int i = 0 ; i <= n ; i++) parent[i] = -1 ; 

	while(s.size()) s.pop() ; 

	for(int i = 0 ; i < n ; i++){
		int last = -1 ; 
		while(!s.empty() && v[s.top()] <= v[i]){//pra min so mudar o sinal 
			last = s.top() ; s.pop() ; 
		}

		if(!s.empty()){
			parent[i] = s.top() ; 
		}

		if(last >= 0){
			parent[last] = i ; 
		}

		s.push(i) ;

	}
	
}
