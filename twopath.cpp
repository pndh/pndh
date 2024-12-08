#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 3e5 + 5;
int n, m;
vector<pair<int,int>> g[mx];
int road[mx];
void read(){
    cin >> n;
    for (int i = 1; i < n; i++){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].pb({y, w});
        g[y].pb({x, w});
    }
}

void dfs(int u, int pa){
    for (auto p: g[u]){
        int v = p.first;
        if (v == pa) continue;
        int dis = p.second;
        road[v] = road[u] ^ dis;
        dfs(v, u);
    }
}

void solve(){
    dfs(1, 1);
//    cout << (road[1] ^ road[3]) << " " << (road[1] ^ road[5]) << '\n';
    for (int u = 1; u <= n; u ++){
        for (int v = u + 1; v <= n; v ++){
            for (int x = 1; x <= n; x ++){
                for (int y = x + 1; y <= n; y ++){
                    if (u == x && v == y) continue;
                    if ((road[u] ^ road[v]) == (road[x] ^ road[y])){
                        cout << u << " " << v << " " << x << " " << y;
                        return;
                    }
                }
            }
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
