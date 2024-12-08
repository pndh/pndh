#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m, q;
const int mx=1e6+5;
const int inf=1e18;
struct tt{
    int l,r,x,y;
};
struct que{
    int p,u,v;
};
int val[mx];
tt qr[mx];
que ask[mx];
void read(){
    cin >> n >> m;
    for (int i=1;i<=n;i++){
        cin >> val[i];
    }
    for (int i=1;i<=m;i++){
        cin >> qr[i].l >> qr[i].r >> qr[i].x >> qr[i].y;
    }
    cin >> q;
    for (int i=1;i<=q;i++){
        cin >> ask[i].p >> ask[i].u >> ask[i].v;
    }
}
bool check1(){
    if (n<=5000 && m <=5000 && q <=5000){
        return true;
    }
    return false;
}
bool check2(){
    for (int i=1;i<=m;i++){
        if (qr[i].l!=1){
            return false;
        }
    }
    for (int i=1;i<=q;i++){
        if (ask[i].u!=1){
            return false;
        }
    }
    return true;
}
void sub1(){
    for (int i=1;i<=q;i++){
        int ans=val[ask[i].p];
        for (int j=ask[i].u;j<=ask[i].v;j++){
            if (ask[i].p>=qr[j].l && ask[i].p<=qr[j].r && ans==qr[j].x){
                ans+=qr[j].y;
            }
        }
        cout << ans << '\n';
    }
}
bool vs[mx];
int ans[mx];
int g[mx];
int dfs(int u){
    if (vs[u]){
        return ans[u];
    }
    vs[u]=true;
    if (g[u]==0){
        ans[u]=u;
        return u;
    }else{
        return ans[u]=dfs(g[u]);
    }
}
void sub2(){
    for (int i=1;i<=m;i++){
        if (g[qr[i].x]==0){
            g[qr[i].x]=qr[i].x+qr[i].y;
        }
    }
    for (int i=1;i<=q;i++){
        cout << dfs(val[ask[i].p]);
    }
}
map<int,set<pair<int,int>>> adj;
struct node{
    int x,y,id;
};
struct ak{
    int u,v,id;
};
vector<node> event[mx];
vector<ak> quest[mx];
int u,v;
int dfs2(int i){
    auto it=adj[i].lower_bound({u,0});
    if (it==adj[i].end()){
        return i;
    }
    pair<int,int> p=*it;
    if (it!=adj[i].end() && p.first<=v){
        return dfs2(p.second);
    }else{
        return i;
    }
}
void sub4(){
    int res[mx];
    for (int i=1;i<=m;i++){
        event[qr[i].l].pb({qr[i].x,qr[i].x+qr[i].y,i});
        event[qr[i].r+1].pb({qr[i].x,qr[i].x+qr[i].y,-i});
    }
    for (int i=1;i<=q;i++){
        quest[ask[i].p].pb({ask[i].u,ask[i].v,i});
    }
    for (int i=1;i<=n;i++){
        for (auto nod:event[i]){
            if (nod.id>0){
                adj[nod.x].insert({nod.id,nod.y});
            }else{
                nod.id*=-1;
                adj[nod.x].erase(adj[nod.x].find({nod.id,nod.y}));
            }
        }
        for (auto hoi:quest[i]){
            u=hoi.u,v=hoi.v;
            res[hoi.id]=dfs2(val[i]);
        }
    }
    for (int i=1;i<=q;i++){
        cout << res[i] << '\n';
    }
}
void solve(){
    if (check1()){
        sub1();
    }else if (check2()){
        sub2();
    }else{
        sub4();
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("cquery.inp","r",stdin);
    freopen("cquery.out","w",stdout);
    read();
    solve();
    return 0;
}