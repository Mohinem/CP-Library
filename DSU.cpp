#include <bits/stdc++.h>
using namespace std;

struct DSU{

    std::vector <int> size;
    std::vector <int> parent;

    DSU(int n){
        size = std::vector <int> (n,1);
        parent = std::vector <int> (n);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }

    int root(int x){

        while(parent[x]!=x){
        
            parent[x]=parent[parent[x]];
            x=parent[x];
        }
        return x;
    }

    void uni(int x,int y){

        if(x==y){
            return;
        }
        
        x=root(x);
        y=root(y);
        
        if(size[x]<size[y]){
            size[y]+=size[x];
            parent[x]=y;
        }
        else{
            size[x]+=size[y];
            parent[y]=x;
        }
    }
};

int main(){

    cout<<"Testing DSU ...\n";
    int dsu_size=6;
    DSU dsu(dsu_size);
    // check if size is 6
    assert(dsu.size.size() == dsu.parent.size() and dsu.size.size()==dsu_size);
    // check if the parent for every node is correct
    for(int i=0;i<6;i++){
        assert(dsu.root(i)==dsu.parent[i] and dsu.root(i)==i);
    }
    dsu.uni(1,2);
    dsu.uni(2,3);
    dsu.uni(1,1);
    // check if the union operation works fine
    assert(dsu.root(1) == dsu.root(2) and dsu.root(1) == dsu.root(3));
    assert(dsu.size[dsu.root(1)] == 3);

    cout<<"Testing passed \n";
    return 0;
}