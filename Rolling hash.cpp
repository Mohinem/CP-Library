/* A small rolling hash snippet. Work is in progress. Also, I haven't had a successful verdict with the snippet yet, so you might want to ignore my snippet.*/


const int HASH_SIZE=2;
const long long BASE=27;

long long mods[4]={1000000007,900000001553,998244353,1000000007};

typedef struct rollhash{
    long long hashval[HASH_SIZE];
    rollhash(){
        for(int i=0;i<HASH_SIZE;i++){
            hashval[i]=0;
        }
    }
};

bool operator < (rollhash le,rollhash ri){
    return le.hashval[0]<ri.hashval[0];
}

rollhash mul_hash(rollhash &pre,long long val){
    rollhash neww;
    for(int i=0;i<HASH_SIZE;i++){
        neww.hashval[i]=(((pre.hashval[i]*BASE)%mods[i])+val)%mods[i];
    }
    return neww;
}

void init(rollhash &cur){
    for(int i=0;i<HASH_SIZE;i++){
        cur.hashval[i]=0;
    }
}
