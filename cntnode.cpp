#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m, k;
const int mx=1e6+5;
vector<int> g[mx];
vector<int> diem[mx];
int h[mx];
int sz[mx];
int res[mx];
int pa[mx];
int ord[mx];
vector<int> tour;
void read(){
    cin >> n >> m >> k;
    tour.pb(0);
    for (int i=2;i<=n;i++){
        int a;
        cin >> a;
        g[a].pb(i);
    }
}
int up[17][mx];
void predfs(int u){
    tour.pb(u);
    ord[u]=tour.size();
    ord[u]--;
    sz[u]=1;
    for (auto v:g[u]){
        h[v]=h[u]+1;
        up[v][0]=u;
        pa[v]=u;
        predfs(v);
        tour.pb(u);
        sz[u]+=sz[v];
    }
}
int rmq[20][mx];
int LG=19;
void prepro(){
    int len=tour.size();
    len--;
    for (int j = 1; j < 17; ++j)
        for (int u = 1; u <= n; ++u)
            up[u][j] = up[up[u][j - 1]][j - 1];
    for (int i=0;i<len;i++){
    for (int i = 1; i <= len; ++i) rmq[0][i] = tour[i];
    for (int j = 1; j <= LG; ++j)
        for (int i = 1; i + (1 << j) - 1 <= len; ++i){
            if (h[rmq[j - 1][i]]<h[rmq[j - 1][i + (1 << (j - 1))]]){
                rmq[j][i]=rmq[j - 1][i];
            }else{
                rmq[j][i]=rmq[j - 1][i + (1 << (j - 1))];
            }
        }
    }
}
int lca(int l,int r){
    l=ord[l],r=ord[r];
    int k = __lg(r - l + 1);
    if (h[rmq[k][l]]<h[rmq[k][r - (1 << k) + 1]]){
        return rmq[k][l];
    }else{
        return rmq[k][r - (1 << k) + 1];
    }
}
int dis(int l,int r){
    int root=lca(l,r);
    return h[l]+h[r]-h[root]*2-1;
}
void dfs(int u){
    int pa=u;
    for (int i=0;i<17;i++){
        if ((1ll<<i)&(m+1)){
            pa=up[pa][i];
        }
    }
    diem[pa].pb(u);
    // cout << pa << " " << u << '\n';
    if (g[u].size()==0){
        res[u]+=(n-sz[u])*(n-sz[u]-1)/2;
        return;
    }
    for (auto v:g[u]){
        dfs(v);
    }
    int l=0,r=0;
    while(l<diem[u].size()){
        int total_size=0;
        while(r<diem[u].size() && dis(diem[u][l],diem[u][r])<=k){
            total_size+=sz[diem[u][r]];
            r++;
        }
        res[u]+=total_size*(total_size-1)/2;
        l=r;
    }
    for (int i=0;i<diem[u].size();i++){
        int v=diem[u][i];
        if (k>m){
            res[u]+=sz[v]*(n-sz[u]);
        }
    }
    res[u]+=(n-sz[u])*(n-sz[u]-1)/2;
    // for (int i=0;i<diem[u].size();i++){
    //     if (h[diem[u][i]])
    // }
}
void solve(){
    h[1]=1;
    predfs(1);
    prepro();
    dfs(1);
    for (int i=1;i<=n;i++){
        cout << res[i] << " ";
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}