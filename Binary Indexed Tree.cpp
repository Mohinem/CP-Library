int n;
long long bits[200000+50];




void inc(int x,long long val){
    
    int xx=x;
    while(xx<=n){
        bits[xx]+=val;
        xx=xx+(xx&-xx);
    }
}

long long que(int pos){
    long long sum=0;
    while(pos){
        sum+=bits[pos];
        pos=pos-(pos&-pos);
    }
    return sum;
}
