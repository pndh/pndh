#include <bits/stdc++.h>
using namespace std;
#define pb push_back
int n, m;
const int mx=1e6+5;
vector<pair<pair<int,int>,int>> qr;
int tree[mx];
int lazy[mx];
const int mod=1e9+7;
void down(int l,int r,int id){
    if (lazy[id]==0) return;
    int mid=(l+r)/2;
    lazy[id]=0;
    tree[2*id]=mid-l+1;
    tree[2*id+1]=r-(mid+1)+1;
    lazy[2*id]=mid-l+1;
}
void update(int l,int r,int x,int y,int id){
    int mid=(l+r)/2;
    if (r<x || l>y){
        return;
    }else if (x<=l && r<=y){
        tree[id]=r-l+1;
        lazy[id]=r-l+1;
        return;
    }
    down(l,r,id);
    update(l,mid,x,y,id*2);
    update(mid+1,r,x,y,id*2+1);
    tree[id]=tree[2*id]+tree[2*id+1];
}
void read(){
    cin >> n >> m;
    for (int i=1;i<=m;i++){
        int p,q,r;
        cin >> p >> q >> r;
        if (p>q){
            swap(p,q);
        }
        qr.pb({{q,p},r});
    }
    sort(qr.begin(),qr.end());
}

void solve(){
    int mxr=0;
    for (int i=0;i<m;i++){
        int q=qr[i].first.first,p=qr[i].first.second,l=qr[i].second;
        if (q>mxr){
            update(1,n,q,q+l-1,1);
        }else{
            if (q+l-1<=mxr) continue;
            int x=mxr-q+1;
            update(1,n,mxr+1,q+l-1,1);
            update(1,n,p,p+x-1,1);
        }
        mxr=max(mxr,q+l-1);
    }
    int po=n-tree[1];
    int res=1;
    for (int i=1;i<=po;i++){
        res*=2;
        res%=mod;
    }
    cout << res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}