string grid[2020];
string pat[2020];
ll H[2020][2020];
ll poll[2020], polc[2020];
 
void solve(int TIMES){ 
    ll A = 970050001;
    ll B = 922558791;
    int n, m, N, M;
 
    cin >> n >> m >> N >> M;
 
    fr(i, n)
        cin >>  pat[i];
    fr(i, N)
        cin >>  grid[i];
 
        poll[0] = polc[0] = 1;
        for (int i = 1; i <= 2019; ++i) {
            poll[i] = poll[i-1] * B % MOD;   // row powers
            polc[i] = polc[i-1] * A % MOD;   // column powers
        }
    
    fr1(i, n){
        fr1(j, m){
            ll val = pat[i-1][j-1];
            H[i][j] = ( val
                + H[i][j-1] * A % MOD
                + H[i-1][j] * B % MOD
                - H[i-1][j-1] * A % MOD * B % MOD
                + MOD ) % MOD;
 
                if(H[i][j]<0) H[i][j]+=MOD;
        }
    }
 
    ll pattern = H[n][m];
 
    fr1(i, N){
        fr1(j, M){
            ll val = grid[i-1][j-1];
            H[i][j] = ( val
                + H[i][j-1] * A % MOD
                + H[i-1][j] * B % MOD
                - H[i-1][j-1] * A % MOD * B % MOD
                + MOD ) % MOD;
 
            if(H[i][j]<0) H[i][j]+=MOD;
        }
    }
 
    int ans=0;
 
    for(int i=1;i<=N-n+1;i++){
        for(int j=1;j<=M-m+1;j++){
            int ii = i+n-1;
            int jj = j+m-1;
 
            // before the double‐loop:
ll rowPow = poll[n];
ll colPow = polc[m];
 
// inside the double‐loop, once you have ii,jj,i,j:
ll a = H[ii][jj];
ll b = (H[ii][j-1]   * colPow) % MOD;
ll c = (H[i-1][jj]   * rowPow) % MOD;
// we do one mod here so the next multiply stays in 64-bit range:
ll d = (H[i-1][j-1] * rowPow % MOD) * colPow % MOD;
 
ll cur = a - b - c + d;
// now just one mod and one fixup:
cur %= MOD;
if (cur < 0) cur += MOD;
 
if (cur == pattern) ans++;
        }
    }
 
    cout << ans << '\n';
    
}
