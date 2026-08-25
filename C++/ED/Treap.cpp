/*
kactl 
[L, R) R nao incluso, index 0 based
operações permitidas: 
- inserir/remover pos i 
- inverter intervalo [l, r]
- somar intervalo [l, r] 
- min/max intervalo [l, r]
- rotacionar um intervalo 
- adicionar x em [l, r]
- kesimo elemento 
	criar treap: dado um vetor a 
	Node* root = nullptr;

	for (int x : a) {
		root = merge(root, new Node(x));
	}

	split: 
	auto [a, b] = split(root, k);
	root = merge(a, b); //juntar novamente depois 
    
    todas operações que trocam a arvore: root = reverseRange(root, l, r); 
	
*/


struct Node {
	Node *l = 0, *r = 0;
	ll val, c = 1;
	ll y ; 
	ll sum, mn, mx ; 
	bool rev = false ; 
	ll add = 0 ; 
	// ll hf, hb; -> se quiser usar hash de string (palindromo etc), hash de string dinamica
	/* Se for usar pra string usar: 
	Node(char val)
        : val(val), y(rand()),
          hf(val), hb(val) {}
	*/

	bool hasSet = false ; 
	ll setVal = 0 ; 
	Node(ll val)
        : val(val), y(rand()),
          sum(val), mn(val), mx(val) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sum(Node* n){ return n ? n->sum : 0 ; } 

/* Se for usar pra string
void Node::recalc() {
    c = cnt(l) + cnt(r) + 1;

    int L = cnt(l);
    int R = cnt(r);

    hf =
        hashF(l) * pw[1 + R]
        + val * pw[R]
        + hashF(r);

    hb =
        hashB(r) * pw[1 + L]
        + val * pw[L]
        + hashB(l);
}

void applyRev(Node* n) {
    if (!n) return;

    swap(n->l, n->r);
    swap(n->hf, n->hb);

    n->rev ^= 1;
}
*/
//recalcula informacoes depois dos filhos mudarem 
void Node::recalc() { //info pai = info esq + info dir + info no
	c = cnt(l) + cnt(r) + 1; 
	
	sum = val;
    mn = mx = val;

    if (l) {
        sum += l->sum;
        mn = min(mn, l->mn);
        mx = max(mx, l->mx);
    }

    if (r) {
        sum += r->sum;
        mn = min(mn, r->mn);
        mx = max(mx, r->mx);
    }

}

//inverter um no -> so aplica pros filhos depois (lazy)
void applyRev(Node* n) {
    if (!n) return;

    swap(n->l, n->r);
    n->rev ^= 1;
}

/*
isola o vetor 
auto [a, bc] = split(root, l);
auto [b, c] = split(bc, r-l);

//aplica
applyAdd(b, 10);

//junta 
root = merge(a, merge(b,c));

*/

//soma x em cada elemento do no n 
void applyAdd(Node* n, ll x) {
    if (!n) return;

    n->val += x;

    n->sum += x * n->c;
    n->mn += x;
    n->mx += x;

    if (n->hasSet)
        n->setVal += x;
    else
        n->add += x;
}
//muda todos valores do no pra x  (elimina qlqr add anterior)
void applySet(Node* n, ll x) {
    if (!n) return;

    n->val = x;

    n->sum = x * n->c;
    n->mn = n->mx = x;

    n->hasSet = true;
    n->setVal = x;

    n->add = 0;
}

//pra lazy 
//antes de descer push ao voltar recalc 
void push(Node* n) {
    if (!n) return;

    if (n->hasSet) {
        applySet(n->l, n->setVal);
        applySet(n->r, n->setVal);

        n->hasSet = false;
    }

    if (n->add != 0) {
        applyAdd(n->l, n->add);
        applyAdd(n->r, n->add);

        n->add = 0;
    }

    if (n->rev) {
        applyRev(n->l);
        applyRev(n->r);

        n->rev = false;
    }
}

/*
split(root, 3) retorna ABC | DEFG 
//sem lazy 
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}

//testar se eh palindromo 
bool palindrome(Node*& t, int l, int r) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    bool ans = (b->hf == b->hb);

    t = merge(a, merge(b, c));

    return ans;
}

*/

//operações com lazy
pair<Node*, Node*> split(Node* n, int k) {
    if (!n) return {};

    push(n);

    if (cnt(n->l) >= k) {
        auto [L, R] = split(n->l, k);

        n->l = R;
        n->recalc();

        return {L, n};

    } else {
        auto [L, R] =
            split(n->r, k - cnt(n->l) - 1);

        n->r = L;
        n->recalc();

        return {n, R};
    }
}

//une os valores de l r nessa ordem
Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;

    push(l);
    push(r);

    if (l->y > r->y) {
        l->r = merge(l->r, r);

        l->recalc();
        return l;

    } else {
        r->l = merge(l, r->l);

        r->recalc();
        return r;
    }
}


//percorrer a treap
/* 
each(root, [&](ll x) {
    cout << x << ' ';
});
*/

template<class F> void each(Node* n, F f) {
    if (!n) return;

    push(n);

    each(n->l, f);
    f(n->val);
    each(n->r, f);
}

//transformar a treap num vetor 
void toVector(Node* n, vector<ll>& a) {
    if (!n) return;

    push(n);

    toVector(n->l, a);

    a.push_back(n->val);

    toVector(n->r, a);
}

//primeira posicao que segue alguma propriedade 
//ex: >= x
int firstAtLeast(Node* n, ll x) {
    if (!n || n->mx < x)
        return -1;

    push(n);

    if (n->l && n->l->mx >= x)
        return firstAtLeast(n->l, x);

    if (n->val >= x)
        return cnt(n->l);

    int ans = firstAtLeast(n->r, x);

    if (ans == -1)
        return -1;

    return cnt(n->l) + 1 + ans;
}

//primeira posicao em [l, r] 
//que satisfaz alguma condicao
int firstAtLeast(
    Node*& t,
    int l,
    int r,
    ll x
) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    int ans = firstAtLeast(b, x);

    if (ans != -1)
        ans += l;

    t = merge(a, merge(b, c));

    return ans;
}

//inserir um valor na posicao pos (0 index)
//pode receber uma treap inteira 
//root = ins(root, new Node(99), 2);

Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}

// root = erase(root, pos);
//remover o elemento da posicao pos
Node* erase(Node* t, int pos) {
    auto [a, bc] = split(t, pos);
    auto [b, c] = split(bc, 1);

    delete b;

    return merge(a, c);
}

// cout << kth(root, 3)->val << '\n';
//acessar o kesimo elemento 
Node* kth(Node* n, int k) {
    if (!n) return nullptr;

    push(n);

    int left = cnt(n->l);

    if (k < left)
        return kth(n->l, k);

    if (k == left)
        return n;

    return kth(n->r, k - left - 1);
}

// root = setPoint(root, 2, 99);
//alterar o kesimo elemento 
Node* setPoint(Node* t, int pos, ll x) {
    auto [a, bc] = split(t, pos);
    auto [b, c] = split(bc, 1);

    applySet(b, x);

    return merge(a, merge(b, c));
}

// root = reverseRange(root, l, r);
//reverter um intervalo [l, r) cuidado final nao incluso
Node* reverseRange(Node* t, int l, int r) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    applyRev(b);

    return merge(a, merge(b, c));
}

//operacao num range 
ll rangeSum(Node*& t, int l, int r) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

	// ll ans = b->mn; // se for minimo 
	// ll ans = b->mx; // se for maximo 
    ll ans = b ? b->sum : 0; //se for soma 

    t = merge(a, merge(b, c));

    return ans;
}

// root = rangeAdd(root, 1, 4, 10);
//somar num range 
Node* rangeAdd(Node* t, int l, int r, ll x) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    applyAdd(b, x);

    return merge(a, merge(b, c));
}

//setar num range 
Node* rangeSet(Node* t, int l, int r, ll x) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    applySet(b, x);

    return merge(a, merge(b, c));
}

// Node* piece = cut(root, 2, 5);
//recupera um pedaco da treap que corresponde ao range 
Node* cut(Node*& t, int l, int r) {
    auto [a, bc] = split(t, l);
    auto [b, c] = split(bc, r - l);

    t = merge(a, c);

    return b;
}

// queremos girar  DEABC em k = 2 
// ABCDE
Node* rotateRight(Node* t, int k) {
    int n = cnt(t);

    if (n == 0) return t;

    k %= n;

    if (k == 0) return t;

    auto [a, b] = split(t, n - k);

    return merge(b, a);
}

Node* rotateLeft(Node* t, int k) {
    int n = cnt(t);

    if (n == 0) return t;

    k %= n;

    auto [a, b] = split(t, k);

    return merge(b, a);
}

// Example application: move the range [l, r) to index k
// ABCDEFGH quero mover CDE pro começo CDEABFG
// move(root, l, r, 0)
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}
