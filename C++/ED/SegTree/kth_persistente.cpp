map<int,int> mp ; 

struct SEG{

	int create(){
		sum.push_back(0) ; e.push_back(0) ; d.push_back(0) ; 
		return sum.size() - 1 ; 
	}

	int upd(int no, int i, int j, int pos, int v){

		int neww = create() ; 
		e[neww] = e[no] ; d[neww] = d[no] ; sum[neww] = sum[no] ; 

		if(i == j){
			sum[neww]++ ; 
			return neww ; 
		}

		if(pos <= meio){
			int aux = upd(e[neww], i, meio, pos, v) ; 
			e[neww] = aux ;
		}

		else{
			int aux = upd(d[neww], meio + 1, j, pos, v) ;
			d[neww] = aux ; 
		}

		sum[neww] = sum[e[neww]] + sum[d[neww]] ; 
		// cout << i << " " << j << " " << sum[neww] << "\n" ; 

		return neww ; 

	}

	int query(int no_fim, int no_ini, int i, int j, int k){

		// cout << i << " " << j << "\n" ; 
		// cout << sum[no_fim] << " " << sum[no_ini] << "\n" ; 

		if(i == j) return i ; 

		if(sum[e[no_fim]] - sum[e[no_ini]] >= k) return query(e[no_fim], e[no_ini], i, meio, k) ; 
		else return query(d[no_fim], d[no_ini], meio + 1, j, k - (sum[e[no_fim]] - sum[e[no_ini]])) ; 

	}

} Seg ; 
