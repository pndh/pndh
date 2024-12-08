#include <bits/stdc++.h>
using namespace std;
#define pb push_back
int n, m;
const int mx=1e6+5;
vector<pair<int,int>> g[mx];
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
pair<int,int> par[mx];
int h[mx];
void read(){
    cin >> n >> m;
}
int block;
void dfs(int u,int pa){
    h[u]=h[pa]+1;
    for (auto v:g[u]){
        if (v.first==pa) continue;
        if (v.first==block) continue;
        par[v.first].first=u;
        par[v.first].second=v.second;
        dfs(v.first,u);
    }
}
void solve(){
    DSU dsu;
    dsu.init(n);
    bool mst=false;
    vector<pair<int,pair<int,int>>> edge;
    for (int i=1;i<=m;i++){
        int x,y,z;
        cin >> x >> y >> z;
        dsu.join_sets(x,y);
        edge.pb({z,{x,y}});
        if (!mst){
            if (dsu.comp==1){
                sort(edge.begin(),edge.end());
                DSU dsu2;
                dsu2.init(n);
                int sum=0;
                vector<pair<int,pair<int,int>>> new_edge;
                for (int j=0;j<edge.size();j++){
                    if (dsu2.find_set(edge[j].second.first)!=dsu2.find_set(edge[j].second.second)){
                        dsu2.join_sets(edge[j].second.first,edge[j].second.second);
                        sum+=edge[j].first;
                        new_edge.pb(edge[j]);
                    }
                }
                cout << sum << '\n';
                mst=true;
                edge=new_edge;
            }else{
                cout << "-1" << '\n';
            }
        }else{
            vector<pair<int,pair<int,int>>> new_edge;
            DSU dsu2;
            dsu2.init(n);
            pair<int,pair<int,int>> p;
            p={z,{x,y}};
            auto pos=lower_bound(edge.begin(),edge.end(),p);
            edge.insert(pos,p);
            // sort(edge.begin(),edge.end());
            int sum=0;
            for (int j=0;j<edge.size();j++){
                if (dsu2.find_set(edge[j].second.first)!=dsu2.find_set(edge[j].second.second)){
                        dsu2.join_sets(edge[j].second.first,edge[j].second.second);
                        sum+=edge[j].first;
                        new_edge.pb(edge[j]);
                    }
            }
            edge=new_edge;
            cout << sum << '\n';
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}