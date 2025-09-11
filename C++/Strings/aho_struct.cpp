vector<string> pat;
struct AhoCorasick {
	enum {alpha = 26, first = 'a'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		for(int i = 0; i < sz(pat); i++) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);
 
		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			for (int i = 0; i < alpha; i++) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	int find(string word) {
		int n = 0;
		vi dp(sz(word) + 1,0); dp[0] = 1;
		for (int j = 0; j < sz(word); j++) {
            char c = word[j];
			n = N[n].next[c - first];
            int at = N[n].end;
            for(int i=0;i<N[n].nmatches;i++){
                dp[j+1] = (dp[j+1] + dp[j+1-sz(pat[at])]) % mod;
                at = backp[at];
            }
		}
		return dp[sz(word)];
	}
	
};
