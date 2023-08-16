// quantos caminhos de tamanho k no grafo? 
const int mod = 1e9 + 7 ;
const int maxn = 110 ; 
 
int n, m, k ; 
 
struct Mat{
	int v[maxn][maxn] ;
	Mat(){
		for(int i = 1 ; i <= n ; i++){
			for(int j = 1 ; j <= n ; j++){
				v[i][j] = 0 ; 
			}
		}
	}
	void id(){
		for(int i = 1 ; i <= n ; i++) v[i][i] = 1 ; 
	}
} ;
 
Mat mult(Mat &a, Mat&b){
	Mat r ; 
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= n ; j++){
			for(int k = 1 ; k <= n ; k++){
				r.v[i][j] = (r.v[i][j] + (1LL*a.v[i][k]*b.v[k][j])%mod)%mod ; 
			}
		}
	}
	return r ; 
 
}
 
Mat expo(Mat a, int b){
 
	Mat r ; 
	r.id() ; 
	while(b){
		if(b%2) r = mult(r, a) ; 
		a = mult(a, a) ; 
		b>>=1 ;
	}
	return r ; 
 
}
 
int32_t main(){
 
	int ans ; 
	cin >> n >> m >> k ; 
	Mat base ; 
	for(int i = 1,a, b ; i <= m ; i++){
		cin >> a >> b ; 
		base.v[b][a] = 1 ; 
	} 
	Mat resp = expo(base, k) ; 
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= n ; j++){
			ans = (ans + resp.v[i][j])%mod ; 
		}
	}
	cout << ans << "\n" ; 
 
}