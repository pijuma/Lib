struct MAXQ{
 
	deque<pair<long long,int>> minq ; 
	int ini, fim ; 
 
	MAXQ(){ ini = 1, fim = 0 ; }
 
	void clear(){ 
		while(minq.size()) minq.pop_back() ; 
		ini = 1, fim = 0 ;
	}
 
	void add(long long val){
		while(!minq.empty() && val >= minq.back().first) minq.pop_back() ; 
		minq.push_back({val, ++fim}) ; 
	}
 
	void pop(){
		if(!minq.empty() && minq.front().second == ini++) minq.pop_front() ; 
	}
 
	long long get(){ return minq.front().first ; }
 
} maxq ; 
