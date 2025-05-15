struct Node{
    char val;
    ll weight, size;
    bool rev = false;
    Node *left, *right;
    Node(char c) : val(c), weight(rng()), size(1), left(NULL), right(NULL){}
} *root;

int size(Node *treap) { return treap ? treap->size : 0; }

void lazyPropagation(Node *treap){
    if(!treap) return;

    if(treap->rev){
        treap->rev = false;
        swap(treap->left, treap->right);
        if(treap->left) treap->left->rev ^= true;
        if(treap->right) treap->right->rev ^= true;
    }
}

void pull(Node *treap){
    if(!treap)  return; 

    lazyPropagation(treap->left); lazyPropagation(treap->right);

    treap->size = 1 + size(treap->left) + size(treap->right);
}

void split(Node *treap, Node *&left, Node *&right, int val){
    if(!treap){
        left = right = NULL;
        return;
    }

    lazyPropagation(treap);

    if(size(treap->left) < val){
        split(treap->right, treap->right, right, val-size(treap->left)-1);
        left = treap;
    }else{
        split(treap->left, left, treap->left, val);
        right = treap;
    }

    pull(treap);
}

void merge(Node *&treap, Node *left, Node *right){
    lazyPropagation(left); lazyPropagation(right);
    if(left == NULL){
        treap = right;
        return;
    }
    if(right == NULL){
        treap = left;
        return;
    }

    if(left->weight < right->weight){
        merge(left->right, left->right, right);
        treap = left;
    }else{
        merge(right->left, left, right->left);
        treap = right;
    }

    pull(treap);
}

void update(Node *treap, int l, int r) {

    Node *a, *b, *c; 

    split(treap, a, b, l);

    split(b, b, c, r - l + 1);

    if (b) { b->rev ^= true;}

   

    merge(treap, a, b);

    merge(treap, treap, c);

}

void solve(int TIMES){
    int n, LL, RR;
    cin >> n >> LL >> RR;

    LL--; RR--;

    string S;
    cin >> S;

    for(auto x : S){
        merge(root, root, new Node(x));
    }

    int q;

    cin >> q;

    fr(i, q){
        char op;

        cin >> op;

        if(op=='Q'){
            char o;
            cin >> o;
            if(o=='R'){
                Node *a, *b, *c, *d;
                split(root, a, b, RR); 
                split(b, c, d, 1);
                cout << c->val;
                merge(b, c, d);
                merge(root, a, b);
            }else{
                Node *a, *b, *c, *d;
                split(root, a, b, LL); 
                split(b, c, d, 1); 
                cout << c->val;
                merge(b, c, d);
                merge(root, a, b);
            }
        }else if(op=='R'){
            update(root, LL, RR);
        }else{
            char o, oo;
            cin >> o >> oo;

            if(o=='L'){
                if(oo=='L'){
                    LL--;
                }else{
                    LL++;
                }
            }else{
                if(oo=='L'){
                    RR--;
                }else{
                    RR++;
                }
            }
        }
    }

    cout << '\n';
    
}
