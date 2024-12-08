#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
const int mod=1e9+7;
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
void read(){

}

void solve(){
    DSU dsu;
    cin >> n >> m;
    dsu.init(n);
    for (int i=1;i<=m;i++){
        int p,q,l;
        cin >> p >> q >> l;
        for (int j=0;j<=l-1;j++){
            dsu.join_sets(p+j,q+j);
        }
    }
    int po=dsu.comp;
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