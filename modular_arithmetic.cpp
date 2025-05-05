#include<bits/stdc++.h>
using namespace std;

#define int long long



struct Mod{
    int mod=998244353;

    Mod(int new_mod){
        mod=new_mod;
    }

    Mod(){

    }

    int add(int x,int y){
        return (x+y)%mod;
    }

    int sub(int x,int y){
        
        return (x-y+mod)%mod;
    }

    int mul(int x,int y){
        return ((x%mod)*(y%mod))%mod;
    }

    int poww(int x,int y){
        
        if(y==0)return 1;
        
        int xx=poww(x,y/2LL);
        xx=mul(xx,xx);
        if(y%2==1){
            xx=mul(xx,x);
        }
        return xx;
    }

    // only works if y is prime, else returns incorrect results
    int divv(int x,int y){
        int yinv=poww(y,mod-2LL);
        return mul(x,yinv);
    }
};

int main(){

    Mod mod;
    cout<<"Testing mod...\n";
    assert(mod.add(998244353,5)==5);
    assert(mod.sub(5,6)==998244352);
    assert(mod.divv(mod.mul(100000,100000),100000)==100000);

    Mod Mod2(5);
    assert(mod.add(4,5)==4);
    assert(mod.sub(4,5)==4);

    cout<<"Tests passed!\n";

    return 0;
}
