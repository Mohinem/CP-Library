/* A small rolling hash snippet. Work is in progress.*/


const int HASH_SIZE=2;
const long long BASE=27;

long long mods[4]={1000000007,998244353,900000001553,1000000007};

long long bases[4]={27,40,55,110};

typedef struct rollhash{
    long long hashval[HASH_SIZE];
    rollhash(){
        for(int i=0;i<HASH_SIZE;i++){
            hashval[i]=0;
        }
    }
};

bool operator < (rollhash le,rollhash ri){
    if(le.hashval[0]==ri.hashval[0]){
        return le.hashval[1]<ri.hashval[1];
    }
    return le.hashval[0]<ri.hashval[0];
}

rollhash mul_hash(rollhash &pre,long long val){
    rollhash neww;
    for(int i=0;i<HASH_SIZE;i++){
        neww.hashval[i]=(((pre.hashval[i]*bases[i])%mods[i])+val)%mods[i];
    }
    return neww;
}

void init(rollhash &cur){
    for(int i=0;i<HASH_SIZE;i++){
        cur.hashval[i]=0;
    }
}
