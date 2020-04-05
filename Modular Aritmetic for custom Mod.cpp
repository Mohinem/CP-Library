long long mod=998244353;

long long add(long long x,long long y,long long mod){
    return (x+y)%mod;
}

long long sub(long long x,long long y,long long mod){
    
    return (x-y+mod)%mod;
}

long long mul(long long x,long long y,long long mod){
    return ((x%mod)*(y%mod))%mod;
}

long long poww(long long x,long long y,long long mod){
    
    if(y==0)return 1;
    
    long long xx=poww(x,y/2LL,mod);
    xx=mul(xx,xx,mod);
    if(y&1)
    xx=mul(xx,x,mod);
    return xx;
    
}
