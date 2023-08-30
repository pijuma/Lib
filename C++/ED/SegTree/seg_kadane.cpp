struct TREE{
	int sum, ans, pref, suf ; 
} ; 
 
int n, q, v[maxn] ;
TREE tree[4*maxn] ; 
 
struct SEG{
 
	TREE join(TREE a, TREE b){
		TREE anss ; 
		anss.sum = a.sum + b.sum ; 
		anss.pref = max(a.pref, a.sum + b.pref) ;
		anss.suf = max(b.suf, b.sum + a.suf) ; 
		anss.ans = max({a.ans, b.ans, a.suf + b.pref}) ;  
		return anss ;
	}
 
	void build(int no, int i, int j){
		if(i == j){
			tree[no].sum = v[i] ; 
			tree[no].pref = tree[no].suf = tree[no].ans = max(0LL, v[i]) ; 
			return ; 
		}
		build(esq, i, meio), build(dir, meio + 1, j) ; 
		tree[no] = join(tree[esq], tree[dir]) ; 
	}
 
	void upd(int no, int i, int j, int pos, int val){
		if(i == j){
			v[i] = val ;
			tree[no].sum = v[i] ; 
			tree[no].pref = tree[no].suf = tree[no].ans = max(0LL, v[i]) ; 
			return ; 
		}
		if(pos <= meio) upd(esq, i, meio, pos, val) ; 
		else upd(dir, meio + 1, j, pos, val) ; 
		tree[no] = join(tree[esq], tree[dir]) ; 
	}
 
} Seg ;
