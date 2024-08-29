bool is_composite[MAX];
int mu[MAX];

void siege(){
    mu[1] = -1;
    for(int i=2; i<MAX; i++){
        if(is_composite[i]) continue;
        mu[i] = -1;
        for(int j=i*i; j<MAX; j+=i)
            is_composite[j] = true;
    }
}

void mobius(){
    siege();
    
    for(int i=4; i<MAX; i++){
        if(mu[i]!=0) continue;
        for(int j=2; j*j<=i; j++)
            if(i%j==0){
                if((i/j)%j!=0)
                    mu[i] = mu[j]*mu[i/j];
                break;
            }
    }
}
