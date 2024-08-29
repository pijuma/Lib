int n, q, v[maxn], tree[4*maxn] ; 
pair<int,int> lazy[4*maxn] ;
 
struct SEG{
	
	void build(int no, int i, int j){
		lazy[no] = {0, 0} ; 
		if(i == j){
			tree[no] = v[i] ; 
			return ; 
		}
		build(esq, i, meio), build(dir, meio + 1, j) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
	void flush(int no, int i, int j){
		if(!lazy[no].first) return ; 
		int n = (j-i+1), a1 = lazy[no].second, q = lazy[no].first ; 
		int an = (a1 + (n-1)*q) ; 
		tree[no] += ((a1+an)*n)/2 ; 
		if(i != j){
			lazy[esq].first += q, lazy[dir].first += q ; 
			lazy[esq].second += a1, lazy[dir].second += ((a1 + (meio + 1 - i)*q)) ;  
		}
		lazy[no] = {0, 0} ; 
	}
 
	void upd(int no, int i, int j, int l, int r){
		flush(no, i, j) ;
		if (i > r || j < l) return ; 
		if (i >= l && j <= r){
			lazy[no] = {1LL, i - l + 1} ; // razao e val inicial 
			flush(no, i, j) ; 
			return ; 
		}
		upd(esq, i, meio, l, r), upd(dir, meio + 1, j, l, r) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
	int query(int no, int i, int j, int l, int r){
		flush(no, i, j) ; 
		if (i > r || j < l) return 0LL ; 
		if (i >= l && j <= r) return tree[no] ;
		return query(esq, i, meio, l, r) + query(dir, meio + 1, j, l, r) ;  
	}
 
} Seg ;
