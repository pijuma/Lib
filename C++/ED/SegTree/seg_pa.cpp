int tree[4*maxn] ;
int type, n, q, l, r, a, d, pos, m ; 
pair<int, int> lazy[4*maxn] ; 
 
struct SEG{
 
	void build(int no, int i, int j){
		lazy[no] = make_pair(0, 0) ; 
		if(i == j){
			tree[no] = 0 ; 
			return ; 
		}
		build(esq, i, meio), build(dir, meio + 1, j) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
	void flush(int no, int i, int j){
		if(lazy[no] == make_pair(0LL, 0LL)) return ; 
		tree[no] += lazy[no].first + lazy[no].second*i ; 
		if(i != j){
			lazy[esq] = make_pair(lazy[esq].first + lazy[no].first, lazy[esq].second + lazy[no].second) ; 
			lazy[dir] = make_pair(lazy[dir].first + lazy[no].first, lazy[dir].second + lazy[no].second) ;
		}
		lazy[no] = make_pair(0, 0) ; 
	}
 
	//só o 1o cara importa
 
	void att(int no, int i, int j, int l, int r, int a, int d){
		flush(no, i, j) ; 
		if(l > j || r < i) return ; 
		if(l <= i && r >= j){
			lazy[no] = make_pair(a - d*l, d) ; 
			flush(no, i, j) ; 
			return ; 
		}
		att(esq, i, meio, l, r, a, d), att(dir, meio + 1, j, l, r, a, d) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
	int query(int no, int i, int j, int pos){
		flush(no, i, j) ;
		if(i == j && i == pos) return tree[no] ; 
		if(pos <= meio) return query(esq, i, meio, pos) ; 
		else return query(dir, meio + 1, j, pos) ; 
	}
 
} seg ;
 
