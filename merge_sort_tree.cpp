#include <bits/stdc++.h>
using namespace std;

#define int long long

/*This snippet is a merge sort tree which queries on how many values are less than a particular value. */

struct MergeSortTree{
    int max_size;
    
    vector <vector <int> > seg;

    MergeSortTree(int new_size){
        max_size=new_size;
        seg = vector <vector <int> > (4*max_size);
    }    

    int lessthan(int val,vector <int> &arr){
        return lower_bound(arr.begin(),arr.end(),val)-arr.begin();
    } 
    
    void build(int node,int l,int r, vector <int> &p){
        if(l==r){
            
            // cout<<node<<" : "<<a[l]<<"\n";
            seg[node].push_back(p[l]);
            return;
        }
        
        int mid=(l+r)/2;
        build(2*node+1,l,mid,p);
        build(2*node+2,mid+1,r,p);
        int i=0,j=0;
        int n=seg[2*node+1].size();
        int m=seg[2*node+2].size();
    
        while(i<n&&j<m){
            if(seg[2*node+1][i]<seg[2*node+2][j]){
                seg[node].push_back(seg[2*node+1][i]);
                i++;
            }
            else{
                seg[node].push_back(seg[2*node+2][j]);
                j++;
            }
        }
    
        while(i<n){
            seg[node].push_back(seg[2*node+1][i]);
            i++;
        }
    
        while(j<m){
            seg[node].push_back(seg[2*node+2][j]);
            j++;
        }
    }
    

    
    int query(int node,int l,int r,int ql,int qr,int val){
        
        // cout<<"l = "<<l<<" , r = "<<r<<" , ql= "<<ql<<" , qr = "<<qr<<"\n";
        if(l==r){
            if(ql<=l&&qr>=r){
                // cout<<"1st return value = "<<seg[node]<<"\n";
                // cout<<"When "<<"l = "<<l<<" , r = "<<r<<" , ql= "<<ql<<" , qr = "<<qr<<"\n";
                return lessthan(val,seg[node]);
            }
            else{
                return 0;
            }
        }
        
        //full overlap
        if(ql<=l&&qr>=r){
            // cout<<"2nd return value = "<<seg[node]<<"\n";
            // cout<<"When "<<"l = "<<l<<" , r = "<<r<<" , ql= "<<ql<<" , qr = "<<qr<<"\n";
            return  lessthan(val,seg[node]);
        }
        else if(qr<l||ql>r){
            // cout<<"ni/gga\n";
            return 0;
        }
        
        int mid=(l+r)/2;
        int le=query(2*node+1,l,mid,ql,qr,val);
        int ri=query(2*node+2,mid+1,r,ql,qr,val);
        return le+ri;
        
    }

    void update(int node,int l,int r,int pos,int val){
        if(l==r){
            if(pos==l){
                int last_value = seg[node][0];
                seg[node].erase(seg[node].begin(),seg[node].end());
                last_value+=val;
                seg[node].push_back(last_value);
            }
            return;
        }

        int mid=(l+r)/2;

        if(l<=pos and pos<=mid){
            update(2*node+1,l,mid,pos,val);
        }

        if(mid+1<=pos and pos<=r){
            update(2*node+2,mid+1,r,pos,val);
        }

        seg[node].erase(seg[node].begin(),seg[node].end());

        int i=0,j=0;
        int n=seg[2*node+1].size();
        int m=seg[2*node+2].size();
    
        while(i<n&&j<m){
            if(seg[2*node+1][i]<seg[2*node+2][j]){
                seg[node].push_back(seg[2*node+1][i]);
                i++;
            }
            else{
                seg[node].push_back(seg[2*node+2][j]);
                j++;
            }
        }
    
        while(i<n){
            seg[node].push_back(seg[2*node+1][i]);
            i++;
        }
    
        while(j<m){
            seg[node].push_back(seg[2*node+2][j]);
            j++;
        }
    }

};

signed main(){

    cout<<"Testing merge sort tree...\n";
    MergeSortTree mst(10);
    vector <int> arr = {1,2,3,4,5,6,7,8,9,10};
    mst.build(0,0,10-1,arr);
    
    
    assert(mst.query(0,0,10-1,2,7,7)==4);

    //arr[4] = 20
    mst.update(0,0,10-1,4,5);
    assert(mst.query(0,0,10-1,2,7,7)==3);

    //arr[4] = 5
    mst.update(0,0,10-1,4,-5);
    assert(mst.query(0,0,10-1,2,7,7)==4);

    //arr[4] = -11
    mst.update(0,0,10-1,4,-16);  
    assert(mst.query(0,0,10-1,2,7,-10)==1);

    //arr[4] = -10
    mst.update(0,0,10-1,4,1);
    assert(mst.query(0,0,10-1,2,7,-10)==0);
    cout<<"Testing passed!\n";
}