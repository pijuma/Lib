// area formada pela intersecção de uma qtd impar de retangulos (2d)  
struct evento{
	int xi, xf, y, tipo ; 
} ; 
 
int n, m ; 
vector<int> val ; 
vector<evento> ev ; 
int tree[4*maxn], lazy[4*maxn] ; 
 
evento make(int ini, int fim, int h, int t){
	evento a ; 
	a.xi = ini, a.xf = fim, a.y = h, a.tipo = t ; 
	return a ;  
}
 
bool cmp(evento a, evento b){
	if(a.y != b.y) return a.y < b.y ; 
	return a.tipo < b.tipo ; 
}
 
int comp(int x){ return lower_bound(val.begin(), val.end(), x) - val.begin() + 1 ; }
 
struct SEG{
 
	void flush(int no, int i, int j){
		if(!lazy[no]) return ; 
		tree[no] = (val[j] - val[i-1]) - tree[no] ; 
		if(i != j){
			lazy[esq] ^= lazy[no], lazy[dir] ^= lazy[no] ; 
		}
		lazy[no] = 0 ; 
	}
 
	void build(int no, int i, int j){
		if(i == j){
			tree[no] = 0 ; 
			return ; 
		}
		build(esq, i, meio), build(dir, meio + 1, j) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
	ll query(){
		flush(1, 1, m) ; 
		return tree[1] ; 
	}
 
	void att(int no, int i, int j, int a, int b){
		flush(no, i, j) ; 
		if(a > j || b < i) return ; 
		if(a <= i && b >= j){
			lazy[no] ^= 1 ; 
			flush(no, i, j) ; 
			return ;  
		}
		att(esq, i, meio, a, b), att(dir, meio + 1, j, a, b) ; 
		tree[no] = tree[esq] + tree[dir] ; 
	}
 
} seg ; 
 
int main(){
 
	cin >> n ; 
 
	for(int i = 1, x1, x2, y1, y2 ; i <= n ; i++){
		cin >> x1 >> y1 >> x2 >> y2 ; 
		int xi = min(x1, x2), xf = max(x1, x2), yi = min(y1, y2), yf = max(y1, y2) ; 
		ev.push_back(make(xi, xf, yi, 0)), ev.push_back(make(xi, xf, yf, 1)) ; 
		val.push_back(xi), val.push_back(xf) ; 
	}
 
	sort(val.begin(), val.end()) ; 
	val.erase(unique(val.begin(), val.end()), val.end()) ; //comp coord x 
 
	sort(ev.begin(), ev.end(), cmp) ; // ordena cres pelo y ou abre 1o 
 
	m = (int) val.size() - 1 ; 
 
	seg.build(1, 1, m) ; // inicializa a seg -> 0 
 
	ll ans = 0, Yi = 0 ; 
 
	for(int i = 0 ; i < (int) ev.size() ; i++){
		ll s = seg.query() ; //qts caras ligados 
		ll aux = 1LL * s * (ev[i].y - Yi) ; // add area 
		seg.att(1, 1, m, comp(ev[i].xi), comp(ev[i].xf) - 1) ;  //novos 
		ans += aux ; 
		Yi = ev[i].y ; 
	}
 
	cout << ans << "\n" ; 
 
}
