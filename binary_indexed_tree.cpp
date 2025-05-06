#include <bits/stdc++.h>
using namespace std;

#define int long long

struct BIT{

    int max_size;
    vector <int> bits;

    BIT(int new_size){
        max_size = new_size;
        bits = vector <int> (new_size+1,0);
    }

    void increase(int x,int val){
        
        int xx=x;
        while(xx<=max_size){
            bits[xx]+=val;
            xx=xx+(xx&-xx);
        }
    }

    int query(int pos){
        int sum=0;
        while(pos){
            sum+=bits[pos];
            pos=pos-(pos&-pos);
        }
        return sum;
    }
};

int main(){
    // Testing
    cout<<"Testing BIT...\n";
    BIT bit (6);
    assert(bit.max_size + 1 == bit.bits.size());

    bit.increase(4,5);
    bit.increase(2,-3);
    bit.increase(6,2);

    assert(bit.query(0)==0);
    assert(bit.query(1)==0);
    assert(bit.query(2)==-3);
    assert(bit.query(3)==-3);
    assert(bit.query(4)==2);
    assert(bit.query(5)==2);
    assert(bit.query(6)==4);
    
    cout<<"Testing passed!\n";
    return 0;
}