 
struct SEG{
    void flush(int no, int i, int j){
       if(!lazy[no]) return ;
       tree[no] += (j-i+1)*lazy[no] ;
       if(i!=j){
        lazy[esq] += lazy[no] ;
        lazy[dir] += lazy[no] ;
       }
       lazy[no] = 0 ;
    }
    void build(int no, int i, int j){
        if(i == j){
            lazy[no] = 0 ;
            tree[no] = x[i] ;
            return ;
        }
        build(esq, i, meio), build(dir, meio + 1, j) ;
        tree[no] = tree[esq]+tree[dir] ;
    }
   void att(int no, int i, int j, int a, int b, int v){
       flush(no, i, j) ;
        if(a > j || b < i) return  ;
        if(a <= i && b >= j){
            lazy[no] = v ;
            flush(no, i, j) ;
            return ;
        }
        att(esq, i, meio, a, b, v), att(dir, meio + 1, j, a, b, v) ;
        tree[no] = tree[esq]+tree[dir] ;
    }
    int query(int no, int i, int j, int a, int b){
        flush(no, i, j) ;
        if(a > j || b < i) return 0 ;
        if(a <= i && b >= j) return tree[no] ;
        return query(esq, i, meio, a, b) + query(dir, meio + 1, j, a, b) ;
    }
} seg;
