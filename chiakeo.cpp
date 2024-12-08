#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
int sang[mx];
void prepro(){
    for (int i=2;i<=sqrt(mx);i++){
        if (sang[i]) continue;
        for (int j=i*i;j<=mx;j+=i){
            sang[j]=i;
        }
    }
    for (int i=2;i<=mx;i++){
        if (!sang[i]) sang[i]=i;
    }
}
int ma[mx];
int prim[mx],hop[mx];
void read(){
    prepro();
    cin >> n >> m;
    for (int i=1;i<=n;i++){
        cin >> ma[i];
    }
}

void solve(){
    for (int i=1;i<=m;i++){
        int type,l,r,v;
        cin >> type >> l >> r >> v;
        if (type==1){
            prim[l]+=v;
            prim[r+1]-=v;
        }else{
            hop[l]+=v;
            hop[r+1]-=v;
        }
    }
    for (int i=1;i<=n;i++){
        prim[i]+=prim[i-1];
        hop[i]+=hop[i-1];
    }
    for (int i=1;i<=n;i++){
        if (ma[i]!=sang[ma[i]]){
            cout << hop[i] << " ";
        }else{
            cout << prim[i] << ' ';
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}