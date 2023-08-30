vector<int> sum, e, d ; 

struct SEG{

	int create(){
		sum.push_back(0) ; 
		e.push_back(0) ; 
		d.push_back(0) ; 
		return sum.size() - 1 ; 
	}

	void upd(int no, int i, int j, int pos, int v){
		
		if(i > j || i > pos) return ; 
		if(i == j && i == pos){
			sum[no] = v ;
			return ;  
		}
		
		if(no == 0) return ; 
		
		if(pos <= meio){

			if(!e[no]){
				int aux = create() ; 
				e[no] = aux ; 
			}

			upd(e[no], i, meio, pos, v) ; 
		
		}

		else{
			
			if(!d[no]){
				int aux = create() ; 
				d[no] = aux ; 
			}

			upd(d[no], meio + 1, j, pos, v) ; 
		
		}

		sum[no] = sum[e[no]] + sum[d[no]] ; 

	}

	int query(int no, int i, int j, int a, int b){
		
		if(i > b || j < a) return 0 ; 
		if(no == 0) return 0 ; 

		if(a <= i && b >= j) return sum[no] ; 

		return query(e[no], i, meio, a, b) + query(d[no], meio + 1, j, a, b) ; 

	}

} Seg ; 
