int sizze[N];
int par[N];

int root(int x){

    while(par[x]!=x){
    
        par[x]=par[par[x]];
        x=par[x];
    }
    return x;
}

void uni(int x,int y){

    if(x==y){
        return;
    }
    
    x=root(x);
    y=root(y);
    
    if(sizze[x]<sizze[y]){
        sizze[y]+=sizze[x];
        par[x]=y;
    }
    else{
        sizze[x]+=sizze[y];
        par[y]=x;
    }
}
