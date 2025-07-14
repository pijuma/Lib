//2^n*n 
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][0] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i+1] = dp[mask][i] + dp[mask^(1<<i)][i]; //nao ligar + ligar 
		else
			dp[mask][i+1] = dp[mask][i];
	}
	F[mask] = dp[mask][N];
}

//memory optimized
for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}
