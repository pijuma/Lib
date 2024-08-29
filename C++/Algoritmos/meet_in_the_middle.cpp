	for(int i = 0 ; i < n ; i++) cin >> v[i] ; 
 
	int esq = (n+1)>>1, dir = (n>>1) ; 
 
	for(int mask = 0 ; mask < (1<<dir) ; mask++){
		int s = 0 ; 
		for(int i = 0 ; i < dir ; i++){
			if(mask&(1<<i)) s += v[i] ; 
		}
		m1.push_back(s) ; 
	}
 
	for(int mask = 0 ; mask < (1<<esq) ; mask++){
		int s = 0 ;
		for(int i = 0 ; i < esq ; i++){
			if(mask&(1<<i)) s += v[i+dir] ; 
		} 
		m2.push_back(s) ; 
	}
 
	sort(m2.begin(), m2.end()) ; 
 
	for(int i = 0 ; i < m1.size() ; i++){
		int v = lower_bound(m2.begin(), m2.end(), x - m1[i]) - m2.begin() ; 
		int u = upper_bound(m2.begin(), m2.end(), x - m1[i]) - m2.begin() ; 
		ans += abs(v-u) ; 
	}
 
	cout << ans << "\n" ; 
