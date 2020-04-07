/*This snippet is a merge sort tree which queries on how many values are less than a particular value. */

const int N=100000+50;
 
vector <int> seg[400000+50];

int lessthan(int val,vector <int> &arr){
    return lower_bound(arr.begin(),arr.end(),val)-arr.begin();
} 
 
void build(int node,int l,int r){
    if(l==r){
        
        // cout<<node<<" : "<<a[l]<<"\n";
        seg[node].push_back(p[l]);
        return;
    }
    
    int mid=(l+r)/2;
    build(2*node+1,l,mid);
    build(2*node+2,mid+1,r);
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
