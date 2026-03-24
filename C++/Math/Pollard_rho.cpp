// Pollard's Rho Alg
// Usa o algoritmo de deteccao de ciclo de Floyd
// com uma otimizacao na qual o gcd eh acumulado
// A fatoracao nao sai necessariamente ordenada
// O algoritmo rho encontra um fator de n,
// e funciona muito bem quando n possui um fator pequeno
// Complexidades (considerando mul constante):
// rho - esperado O(n^(1/4)) no pior caso
// fact - esperado menos que O(n^(1/4) log(n)) no pior caso

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;
	ll ans = pow(mul(x, x, m), y/2, m);
	return y%2 ? mul(x, ans, m) : ans;
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;

	ll r = __builtin_ctzll(n - 1), d = n >> r;
	for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ll x = pow(a, d, n);
		if (x == 1 or x == n - 1 or a % n == 0) continue;
		
		for (ll j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) break;
		}
		if (x != n - 1) return 0;
	}
	return 1;
}

ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	auto f = [n](ll x) {return mul(x, x, n) + 1;};

	ll x = 0, y = 0, t = 30, prd = 2, x0 = 1, q;
	while (t % 40 != 0 or gcd(prd, n) == 1) {
		if (x==y) x = ++x0, y = f(x);
		q = mul(prd, abs(x-y), n);
		if (q != 0) prd = q;
		x = f(x), y = f(f(y)), t++;
	}
	return gcd(prd, n);
}

vector<ll> fact(ll n) {
	if (n == 1) return {};
	if (prime(n)) return {n};
	ll d = rho(n);
	vector<ll> l = fact(d), r = fact(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

vector<pii> freq_primes(vector<ll>v, ll pot){
	vector<pair<ll , ll>> ans ;//primo e freq  
	map<ll,ll> mp ; 
	for(auto a : v) mp[a]++ ; 
	for(auto a : mp){
		ans.pb({a.ff, 2*a.ss}) ;
	}
	return ans ; 
}

void print(__int128_t n){
    vector<ll> ans ; 
    while(n){
        ans.pb(ll(n%10)) ; n /= 10 ; 
    }
    reverse(ans.begin(), ans.end()) ; 
    for(auto a : ans) cout << a ;
}

__int128_t r1, r2, sum ; 
vector<pii>  primes ; 
ll k ; 
__int128_t kk ; 


//montar todos divisores 
//dado os primos e expoentes que aparecem quero achar todos divisores que eles geram 
void dfs(int id, __int128_t val){

	if(id >= primes.size()){
		__int128_t a = val, b = kk/val ; 
		a = __int128_t(a + k) ; b = __int128_t(b+k) ; 
		if(a%2 || b%2) return ; 
		a = __int128_t(a/2), b = __int128_t(b/2) ; 
		if(sum == -1 || sum > __int128_t(a + b)){
			if(a == b) return ; 
			sum = __int128_t(a + b) ; 
			if(a > b) swap(a, b) ; 
			r1 = a, r2 = b ; 
		}
		return ; 
	}

	for(int i = 0 ; i <= primes[id].ss ; i++){
		dfs(id+1, val) ; val *= primes[id].ff ; 
	}

}

int32_t main() {
  
    cin >> k ; 
    
	  kk = (__int128_t)k * (__int128_t)k ; 

    sum = -1 ; 

    vector<ll> divs ; 

    vector<ll> new_divs ;

    //achar os fatores de k -> fatores de k*k sao os fatores ao quadrado 
    
	  auto resp = fact(k);

    primes = freq_primes(resp, 2) ;//considerando k^2
  
  	dfs(0, 1) ; 

}
