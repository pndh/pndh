#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m, k ,q;
const int mx=5e5+5;
const int inf=1e18;
int d[mx];
vector<pair<int,int>> g[mx];
vector<pair<int,pair<int,int>>> edge;
vector<pair<int,int>> tree[mx];
int up[20][mx];
int gup[20][mx];
int h[mx];
void read(){
    cin >> n >> m >> k >> q;
    for (int i=1;i<=m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].pb({v,w});
        g[v].pb({u,w});
        edge.pb({w,{u,v}});
    }
    for (int i=1;i<= k;i++){
        int x; cin >> x;
        g[0].pb({x,0});
    }
}

void dijkstra(){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,0});
    for (int i=1;i<=n;i++){
        d[i]=inf;
    }
    while (!pq.empty()){
        int u=pq.top().second;
        // int dis=pq.top().first;
        pq.pop();
        for (auto p:g[u]){
            int v=p.first,dis=p.second;
            if (d[v]<d[u]+dis) continue;
            d[v]=d[u]+dis;
            pq.push({d[v],v});
        }
    }
    
}

void dfs(int u,int pa){
    for (auto p:tree[u]){
        int v=p.first,dis=p.second;
        if (v==pa) continue;
        // cout << u << " " << v << 'w' << '\n';
        h[v]=h[u]+1;
        up[0][v]=u;
        gup[0][v]=dis;
        dfs(v,u);
    }
}

struct DSU{
    vector<int> p, sz;
    int comp;

    void init(int n){
        p.resize(n + 2, 0);
        sz.resize(n + 2, 0);
        comp = n;
        for(int i = 1; i <= n; ++i)
            p[i] = i, sz[i] = 1;
    }

    int find_set(int u){
        return u == p[u] ? u : p[u] = find_set(p[u]);
    }

    bool join_sets(int u, int v){
        u = find_set(u), v = find_set(v);
        if(u == v)
            return 0;
        --comp;
        if(sz[u] < sz[v])
            swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
        return 1;
    }
};
int lo2[mx];
void prepro(){
    for (int j=1;j<=19;j++){
        for (int i=1;i<=n;i++){
            up[j][i]=up[j-1][up[j-1][i]];
            gup[j][i]=min(gup[j-1][up[j-1][i]],gup[j-1][i]);
        }
    }
    for (int i=2;i<=n;i++){
        lo2[i]=lo2[i/2]+1;
    }
}
int findis(int a,int b){
    int res=min(d[a],d[b]);
    if (h[a] != h[b]) {
        if (h[a] < h[b]) swap(a, b);
        int dis = h[a] - h[b];
        for (int j = 0; (1 << j) <= k; ++j)
            if (dis >> j & 1) {
                res=min(gup[j][a],res);
                a = up[j][a];
            }
    }
    if (a == b) return res;
    int k=lo2[a];
    for (int j = k; j >= 0; --j){
        if (up[j][a] != up[j][b]){
            res=min(min(gup[j][a],gup[j][b]),res);
            a = up[j][a], b = up[j][b];
        }
    }
    res = min(res,min(gup[0][a],gup[0][b]));
    return res;
}
void solve(){
    dijkstra();
    for (auto &road:edge){
        road.first = min(d[road.second.first],d[road.second.second]);
    }
    sort(edge.begin(),edge.end(),greater<pair<int,pair<int,int>>>());
    DSU dsu;
    dsu.init(n);
    for (auto road : edge){
        if (dsu.find_set(road.second.first)!=dsu.find_set(road.second.second)){
            dsu.join_sets(road.second.first,road.second.second);
            tree[road.second.first].pb({road.second.second,road.first});
            tree[road.second.second].pb({road.second.first,road.first});
            // cout << road.second.first << " " << road.second.second << '\n';
        }
    }
    dfs(1,1);
    prepro();
    for (int i=1; i<=q;i++){
        int a,b;
        cin >> a >> b;
        cout << findis(a,b) << '\n';
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // freopen("walk.inp","r",stdin);
    // freopen("walk.out","w",stdout);
    read();
    solve();
    return 0;
}