#include<bits/stdc++.h>
using namespace std;

#define int long long
//This snippet of code can be used to do maximum subarray sum query, logn time per query

//Code doesn't handle negative maximum value yourself.
//So in case the output of this snippet is 0, find the max value in the range using segtree or maybe sparse table

struct SegTree{

    static constexpr int NEG_INF = LLONG_MIN/2;

    struct single_node{
        int total;
        int maxsubseg;
        int prefix;
        int suffix;
    };

    int max_size;

    vector <int> maxseg;
    vector <int> totseg;
    vector <int> maxpref;
    vector <int> maxsuff;

    SegTree(vector <int> a){
        max_size = a.size();
        maxseg = vector <int>(4*max_size);
        totseg = vector <int>(4*max_size);
        maxpref = vector <int>(4*max_size);
        maxsuff = vector <int>(4*max_size);
        build(0,0,max_size-1,a);
    }

    void build(int node,int l,int r, vector<int>& a){
        if(l==r){
            totseg[node]   = a[l];
            maxpref[node]  = a[l];
            maxsuff[node]  = a[l];
            maxseg[node]   = a[l];
            return;
        }
        int mid=(l+r)/2;
        build(2*node+1, l,   mid, a);
        build(2*node+2, mid+1, r,   a);

        totseg[node] = totseg[2*node+1] + totseg[2*node+2];

        maxpref[node] = max(
            maxpref[2*node+1],
            totseg[2*node+1] + maxpref[2*node+2]
        );
        maxsuff[node] = max(
            maxsuff[2*node+2],
            totseg[2*node+2] + maxsuff[2*node+1]
        );
        maxseg[node] = max({
            maxseg[2*node+1],
            maxseg[2*node+2],
            maxsuff[2*node+1] + maxpref[2*node+2]
        });
    }


    single_node query(int node,int l,int r,int ql,int qr){
        // 1) no overlap
        if (qr < l || ql > r) {
            return single_node{
                /* total */    0,
                /* maxsubseg */NEG_INF,
                /* prefix */   NEG_INF,
                /* suffix */   NEG_INF
            };
        }
        // 2) fully inside
        if (ql <= l && r <= qr) {
            return single_node{
                totseg[node],
                maxseg[node],
                maxpref[node],
                maxsuff[node]
            };
        }
        // 3) partial – recurse & merge
        int mid = (l+r)/2;
        auto le = query(2*node+1, l,   mid, ql, qr);
        auto ri = query(2*node+2, mid+1, r,   ql, qr);

        single_node res;
        res.total     = le.total + ri.total;
        res.prefix    = max(le.prefix,    le.total + ri.prefix);
        res.suffix    = max(ri.suffix,    ri.total + le.suffix);
        res.maxsubseg = max({ le.maxsubseg,
                            ri.maxsubseg,
                            le.suffix + ri.prefix });
        return res;
    }



};

signed main(){

    cout<<"Testing max subarray segtree...\n";
    vector <int> a = {2,5,-3,7,-10,4,-3,-2};
    SegTree segtree(a);
    assert(segtree.query(0,0,a.size()-1,0,1).maxsubseg == 7);
    assert(segtree.query(0,0,a.size()-1,0,2).maxsubseg == 7);
    assert(segtree.query(0,0,a.size()-1,0,3).maxsubseg == 11);
    // cout<<segtree.query(0,0,a.size()-1,2,2).maxsubseg<<"##\n";
    assert(segtree.query(0,0,a.size()-1,2,2).maxsubseg == -3);
    assert(segtree.query(0,0,a.size()-1,3,4).maxsubseg == 7);
    assert(segtree.query(0,0,a.size()-1,4,5).maxsubseg == 4);
    assert(segtree.query(0,0,a.size()-1,1,3).maxsubseg == 9);
    assert(segtree.query(0,0,a.size()-1,4,5).maxsubseg == 4);
    assert(segtree.query(0,0,a.size()-1,6,7).maxsubseg == -2);
    assert(segtree.query(0,0,a.size()-1,6,6).maxsubseg == -3);
    assert(segtree.query(0,0,a.size()-1,7,7).maxsubseg == -2);
    assert(segtree.query(0,0,a.size()-1,4,4).maxsubseg == -10);
    cout<<"Testing passed!\n";
}