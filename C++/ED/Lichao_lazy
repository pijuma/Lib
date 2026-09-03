struct RETA{
    int k, x ; 
};

struct T{
    RETA reta ;
    int max_esq, max_dir, bestVal, bestPos ;
    bool tem_linha ; 
};

struct SEG{

    int f(RETA reta, int i){
        return reta.k*i + reta.x ;  
    }

    void build(int no, int i, int j){
        tree[no].reta.x = tree[no].reta.k = -inf ; 
        tree[no].max_dir = j, tree[no].max_esq = i ; 
        tree[no].bestVal = inf ; tree[no].bestPos = -1 ; tree[no].tem_linha = 0 ; 
        if(i == j) return ; 
        build(esq, i, meio) ; build(dir, meio + 1, j) ; 
    }

    void tentar(int no, int pos, int val){
        if(pos == -1) return ; 
        if (val < tree[no].bestVal ||
            (val == tree[no].bestVal && pos > tree[no].bestPos)) {
            tree[no].bestVal = val;
            tree[no].bestPos = pos;
        }
    }

    void pull(int no, int i, int j){
        
        //pegar os valores dos filhos que ainda existem 
        if (i != j) {
            if (tree[esq].max_esq != -1)
                tree[no].max_esq = tree[esq].max_esq;
            else
                tree[no].max_esq = tree[dir].max_esq;

            if (tree[dir].max_dir != -1)
                tree[no].max_dir = tree[dir].max_dir;
            else
                tree[no].max_dir = tree[esq].max_dir;
        }

        tree[no].bestPos = -1 ; tree[no].bestVal = inf ; 

        if(tree[no].tem_linha && tree[no].max_esq != -1){//com a reta no proprio no
            int pe = tree[no].max_esq, pd = tree[no].max_dir ; 
            tentar(no, pe, f(tree[no].reta, pe)) ; 
            tentar(no, pd, f(tree[no].reta, pd)) ; 
        }

        if(i != j){//melhor valor nos filhos? 
            tentar(no, tree[esq].bestPos, tree[esq].bestVal) ; 
            tentar(no, tree[dir].bestPos, tree[dir].bestVal) ; 
        }
    }

    void att(int no, int i, int j, RETA r){
        //se nao tem linha -> essa passa a ser a nova -> atualizo pros fi
        if(!tree[no].tem_linha){
            tree[no].tem_linha = 1 ; 
            tree[no].reta = r ; 
            
            pull(no, i, j) ; return ;

        }
    
        //vejo se a reta nova eh mlr q a antiga 

        bool novaMelhorEsq =
        f(r, i) < f(tree[no].reta, i);

        bool novaMelhorMeio =
            f(r, meio) < f(tree[no].reta, meio);

        if(novaMelhorMeio) swap(r, tree[no].reta) ;
        
        if(i != j){
            if(novaMelhorEsq != novaMelhorMeio) att(esq, i, meio, r) ; 
            else att(dir, meio + 1, j, r) ; 
        }

        pull(no, i, j) ; 
    
    }

    void addReta(int no, int i, int j, int a, int b, RETA reta){
        if(i > b || j < a) return ; 
        if(a <= i && b >= j){
            
            att(no, i, j, reta) ; 

            pull(no, i, j) ; 

            return ; 

        }
        
        addReta(esq, i, meio, a, b, reta) ; addReta(dir, meio + 1, j, a, b, reta) ; 
        
        pull(no, i, j) ; 
    }

    void set_vis(int no, int i, int j, int pos){
        if(i == j){ //nao posso mais usar 
            tree[no].max_dir = tree[no].max_esq = -1 ; 
            tree[no].bestPos = -1 ; tree[no].bestVal = inf ;
            return ; 
        }
        if(pos <= meio) set_vis(esq, i, meio, pos) ; 
        else set_vis(dir, meio + 1, j, pos) ; 

        pull(no, i, j) ; //atualizar o nó atual qd filhos mudaram 

    }

    pii query(int no, int i, int j){
        return {tree[no].bestPos, tree[no].bestVal} ; 
    }


}Seg ;

// Li-Chao Tree - Lazy
//
// Sendo N = MA-MI:
// insert({a, b}) minimiza tudo com ax+b - O(log N)
// insert({a, b}, l, r) minimiza com ax+b no range [l, r] - O(log^2 N)
// shift({a, b}) soma ax+b em tudo - O(1)
// shift({a, b}, l, r) soma ax+b no range [l, r] - O(log^2 N)
// query(x) retorna o valor da posicao x - O(log N)
//
// No inicio eh tudo LINF, se inserir {0, 0} fica tudo 0
//
// O(n log N) de memoria ; O(n) de memoria se nao usar as operacoes de range

template<int MI = int(-1e9), int MA = int(1e9)> struct lichao {
	struct line {
		ll a, b;
		ll la, lb; // lazy
		array<int, 2> ch;
		line(ll a_ = 0, ll b_ = LINF) :
			a(a_), b(b_), la(0), lb(0), ch({-1, -1}) {}
		ll operator ()(ll x) { return a*x + b; }
	};
	vector<line> ln;

	int ch(int p, int d) {
		if (ln[p].ch[d] == -1) {
			ln[p].ch[d] = ln.size();
			ln.emplace_back();
		}
		return ln[p].ch[d];
	}
	lichao() { ln.emplace_back(); }

	void prop(int p, int l, int r) {
		if (ln[p].la == 0 and ln[p].lb == 0) return;
		ln[p].a += ln[p].la, ln[p].b += ln[p].lb;
		if (l != r) {
			int pl = ch(p, 0), pr = ch(p, 1);
			ln[pl].la += ln[p].la, ln[pl].lb += ln[p].lb;
			ln[pr].la += ln[p].la, ln[pr].lb += ln[p].lb;
		}
		ln[p].la = ln[p].lb = 0;
	}

	ll query(int x, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		ll ret = ln[p](x);
		if (ln[p].ch[0] == -1 and ln[p].ch[1] == -1) return ret;
		int m = l + (r-l)/2;
		if (x <= m) return min(ret, query(x, ch(p, 0), l, m));
		return min(ret, query(x, ch(p, 1), m+1, r));
	}

	void push(line s, int p, int l, int r) {
		prop(p, l, r);
		int m = l + (r-l)/2;
		bool L = s(l) < ln[p](l);
		bool M = s(m) < ln[p](m);
		bool R = s(r) < ln[p](r);
		if (M) swap(ln[p].a, s.a), swap(ln[p].b, s.b);
		if (s.b == LINF) return;
		if (L != M) push(s, ch(p, 0), l, m);
		else if (R != M) push(s, ch(p, 1), m+1, r);
	}
	void insert(line s, int a=MI, int b=MA, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		if (a <= l and r <= b) return push(s, p, l, r);
		if (b < l or r < a) return;
		int m = l + (r-l)/2;
		insert(s, a, b, ch(p, 0), l, m);
		insert(s, a, b, ch(p, 1), m+1, r);
	}

	void shift(line s, int a=MI, int b=MA, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		int m = l + (r-l)/2;
		if (a <= l and r <= b) {
			ln[p].la += s.a, ln[p].lb += s.b;
			return;
		}
		if (b < l or r < a) return;
		if (ln[p].b != LINF) {
			push(ln[p], ch(p, 0), l, m);
			push(ln[p], ch(p, 1), m+1, r);
			ln[p].a = 0, ln[p].b = LINF;
		}
		shift(s, a, b, ch(p, 0), l, m);
		shift(s, a, b, ch(p, 1), m+1, r);
	}
};
