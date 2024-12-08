#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, m;
int timeDFS, timer, walk[2 * mx], tin[mx], tout[mx], h[mx], fi[mx];
vector<int> g[mx];

void read(){
    cin >> n >> m;
}


void pre_dfs(int u, int pre){
    tin[u] = ++timeDFS;
    walk[++timer] = u;
    fi[u] = timer;
    for(int v : g[u]){
//        cout << u << " " << v << '\n';
        if(v == pre)
            continue;
        h[v] = h[u] + 1;
        pre_dfs(v, u);
        walk[++timer] = u;
    }
    tout[u] = timeDFS;
}
const int LG = 20;
pair<int,int> st[LG + 1][2 * mx];

void build_st(){
    for(int i = 1; i <= timer; ++i)
        st[0][i] = {h[walk[i]], walk[i]};
    for(int k = 1; k <= LG; ++k)
        for(int i = 1; i + (1 << k) - 1 <= timer; ++i)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
}

int lca(int u, int v){
    if(fi[u] > fi[v])
        swap(u, v);
    int k = __lg(fi[v] - fi[u] + 1);
    return min(st[k][fi[u]], st[k][fi[v] - (1 << k) + 1]).second;
}

int d[mx];

void bfs(int x){
    queue<pair<int,int>> q;
    q.push({0, 0});
    for (int i = 1; i <= n; i++){
        d[i] = inf;
    }

    while (!q.empty()){
        int u = q.front().first;
        int dis = q.front().second;
        q.pop();
        for (auto v : g[u]){
//            cout << u << " " << v << '\n';
            if (d[v] == inf){
                d[v] = dis + 1;
                q.push({v, d[v]});
            }
        }
    }
}

void solve(){
    int block_size = sqrt(m);
    vector<int> cand;
    for (int i = 1; i <= n; i++){
        d[i] = inf;
    }
    for (int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    pre_dfs(1, 1);
    build_st();
    cand.pb(1);
    for (int i = 1; i <= m; i++){
        int qry, u;
        cin >> qry >> u;
        if (qry == 1){
            cand.pb(u);
        }else{
            int res = n;
            for (auto v : cand){
//                cout << u << " " <<  v << " " << lca(u, v) << '\n';
                res = min(res,h[u] + h[v] - 2 * h[lca(v, u)]);
            }
            cout << min(d[u] - 1, res) << '\n';
        }
        if (i % block_size == 0){
            for (auto x : cand){
                g[0].pb(x);
            }
            bfs(0);
            cand.clear();
        }
    }

}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    if(fopen(task".inp", "r")){
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    read();
    solve();
}
