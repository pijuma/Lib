// gcd(a, m) = 1 para existir solucao
// ax + my = 1, ou a*x = 1 (mod m)
int gcd(int a, int b, int &i, int &j){
    if(!b){
        i = 1;
        j = 0;
        return a;
    }

    int d = gcd(b, a % b, i, j);

    int lsti = i;
    int lstj = j;

    i = lstj;
    j = lsti - lstj * (a / b);

    return d;
}

ll inv(ll a){
    int i, j;

    int d = gcd(a, mod, i, j);

    return (i % mod + mod) % mod;
}

ll inv(ll a, ll phim) { // com phi(m), se m for primo entao phi(m) = p-1
	ll e = phim-1;
	return fexp(a, e);
}
