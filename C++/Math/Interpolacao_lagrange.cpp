#include <bits/stdc++.h>
#define ll long long 
using namespace std ; 
 
const int maxn = 1e6 + 5 ;
const long long MOD = 1e9 + 7;
 
ll exp(ll a, ll b) {
	ll ans = 1 ; 
    while(b){
        if(b&1) ans = (ans*a)%MOD ;
        a = (a*a)%MOD ; b>>=1 ;
    }
    return ans ;
}
 
ll fat[maxn], ifat[maxn];
 
class LagrangePoly {
public:
	LagrangePoly(std::vector<long long> _a) {
		//f(i) = _a[i]
		//interpola o vetor em um polinomio de grau y.size() - 1
		y = _a;
		den.resize(y.size());
		int n = (int) y.size();
		for(int i = 0; i < n; i++) {
			y[i] = (y[i] % MOD + MOD) % MOD;
			den[i] = ifat[n - i - 1] * ifat[i] % MOD;
			if((n - i - 1) % 2 == 1) {
				den[i] = (MOD - den[i]) % MOD;
			}
		}
	}
	
	long long getVal(long long x) {
		int n = (int) y.size();
		x %= MOD;
		if(x < n) {
			//return y[(int) x];
		}
		std::vector<long long> l, r;
		l.resize(n);
		l[0] = 1;
		for(int i = 1; i < n; i++) {
			l[i] = l[i - 1] * (x - (i - 1) + MOD) % MOD;
		}
		r.resize(n);
		r[n - 1] = 1;
		for(int i = n - 2; i >= 0; i--) {
			r[i] = r[i + 1] * (x - (i + 1) + MOD) % MOD;
		}
		long long ans = 0;
		for(int i = 0; i < n; i++) {
			long long coef = l[i] * r[i] % MOD;
			ans = (ans + coef * y[i] % MOD * den[i]) % MOD;
		}
		return ans;
	}
	
private:
	vector<ll> y, den;
};
 
int main(){
    // montar o fatorial e o inverso exp(fat[i], mod-2) 
    // faz um vetor que calcula soma ate x^k pra x de 1 a k+1
    // joga o vetor no lagrange e pega val 
	int n, k ; cin >> n >> k ; 
    
    fat[0] = 1, ifat[0] = 1 ; 
    
    for(int i = 1 ; i < maxn ; i++){
        fat[i] = (fat[i-1]*i)%MOD ; 
        ifat[i] = exp(fat[i], MOD-2) ; 
    }

    vector<ll> t ; 

    t.push_back(0) ; 

    for(int i = 1 ; i <= k + 1 ; i++){
        t.push_back((t.back() + exp(i, k))%MOD) ;
    }

    LagrangePoly lag(t) ; 
    
    cout << lag.getVal(n) << "\n" ; 

}
