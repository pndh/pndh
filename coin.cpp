#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m, q;
const int mx=1e6+5;
const int inf=1e18;
int root[mx];
int sz[mx];
int res[mx];
vector<int> g[mx];
int last[mx];
int goin[mx];
int dept[mx];
void read(){
    cin >> n >> m >> q;
    for (int i=1;i<=m;i++){
        root[i]=i;
        sz[i]=1;
    }
}
int find_roots(int a){
    if (root[a]==a){
        return a;
    }
    root[a]=find_roots(root[a]);
    return root[a];
}
void dsu(int a,int b){
    a=find_roots(a),b=find_roots(b);
    if (sz[a]>sz[b]){
        root[b]=root[a];
    }else{
        root[a]=root[b];
    }
}
int calc(int u){
    if (last[u]){
        return last[u];
    }
    last[u]=dept[u];
    for (auto x:g[u]){
        last[u]=max(last[u],calc(x));
        // cout << u << " " << x << '\n
    }
    return last[u];
}
void solve(){
    vector<pair<int,int>> edge;
    for (int i=1;i<=q;i++){
        int x=0,y=0;
        char type;
        string s;
        cin >> s;
        int id=0;
        while(s[id]!='<' && s[id]!='='){
            x*=10;
            x+=s[id]-'0';
            id++;
        }
        type=s[id];
        id++;
        while(id<s.size()){
            y*=10;
            y+=s[id]-'0';
            id++;
        }
        if (type=='<'){
            edge.pb({x,y});
        }else{
            dsu(x,y);
        }
    }
    for (auto x:edge){
        g[find_roots(x.first)].pb(find_roots(x.second));
        goin[find_roots(x.second)]++;
    }
    queue<pair<int,int>> topo;
    for (int i=1;i<=m;i++){
        if (find_roots(i)==i){
            if (goin[i]==0){
                topo.push({i,1});
                dept[i]=1;
            }
        }
    }
    while(!topo.empty()){
        int u=topo.front().first;
        // cout << u << '\n';
        int dep=topo.front().second;
        topo.pop();
        for (auto x:g[u]){
            goin[x]--;
            if (goin[x]==0){
                topo.push({x,dep+1});
                dept[x]=dep+1;
            }
        }
    }
    for (int i=1;i<=m;i++){
        if (find_roots(i)==i){
            calc(i);
            if (last[i]==n){
                res[i]=dept[i];
            }
        }
    }
    for (int i=1;i<=m;i++){
        if (res[find_roots(i)]){
            cout << 'K' << res[find_roots(i)] << '\n';
        }else{
            cout << "?" << '\n';
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("coin.inp","r",stdin);
    freopen("coin.out","w",stdout);
    read();
    solve();
    return 0;
}