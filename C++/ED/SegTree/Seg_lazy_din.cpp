struct SEG{

	int create(){
		mx.push_back(0) ; 
		e.push_back(0) ; 
		d.push_back(0) ; 
		lazy.push_back(0) ;
		return mx.size() - 1 ; 
	}

	void flush(int no, int i, int j){
		mx[no] += lazy[no] ; 
		if(i != j){
			if(e[no] == 0){
				int aux = create() ; 
				e[no] = aux ;
			}
			if(d[no] == 0){
				int aux = create() ; 
				d[no] = aux ;
			}
			// cout << e[no] << " " << d[no] << "\n" ; 
			lazy[e[no]] += lazy[no] ; lazy[d[no]] += lazy[no] ; 
		}
		lazy[no] = 0 ; 
	}

	void upd(int no, int i, int j, int a, int b, int v){
		if(i > j || !no) return ; 
		if(lazy[no]) flush(no, i, j) ; 
		if(i > b || j < a) return ; 

		if(a <= i && b >= j){
			lazy[no]++ ; 
			flush(no, i, j) ;
			return ; 
		}

		if(e[no] == 0){
		    int aux = create() ; e[no] = aux ;  
		}
		if(d[no] == 0){
			int aux = create() ; d[no] = aux ;  
		} 

		upd(e[no], i, meio, a, b, v), upd(d[no], meio + 1, j, a, b, v) ; 

		mx[no] = max(mx[e[no]], mx[d[no]]) ; 
	
	}

	int query(int no, int i, int j, int a, int b){
		if(i > j || !no) return 0 ; 
		if(lazy[no]) flush(no, i, j) ; 
		if(i > b || j < a) return 0 ; 
		if(a <= i && b >= j) return mx[no] ; 
		int aa = 0, bb = 0 ; 
		if(e[no]) aa = query(e[no], i, meio, a, b) ;
		if(d[no]) bb = query(d[no], meio + 1, j, a, b) ;
		return max(aa, bb) ; 
	}

} Seg ; 
