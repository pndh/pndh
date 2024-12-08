#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "yagi"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, q;
struct edge{
    int v, chieu, id;
};
vector<edge> g[mx];

pair<int,int> E[mx];

void read(){
    cin >> n;
    for (int i = 1; i < n; i++){
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        E[i] = {x, y};
        g[u].pb({v, true, i});
        g[v].pb({u, false, i});
    }

    cin >> q;
}

namespace mim{
    bool valid(){
        if (q == 1){
            return true;
        }
    }
    pair<int,int> dp[mx];
    int h1[mx], h0[mx];
    int h[mx], max_h[mx];
    vector<int> lens;
    int tongin = 0;
    void pre_dfs(int u, int p){
        for (auto &pa : g[u]){
            int v = pa.v;
            if (v == p) continue;
//            cout << u << " " << v << '\n';
            int i = pa.id;
            if (pa.chieu == false){
                swap(E[i].first, E[i].second);
            }
            h1[v] = h1[u] + E[i].first;
            h0[v] = h0[u] + E[i].second;
            pre_dfs(v, u);
        }
    }

    void pre_dfs_hld(int u, int pa){
        max_h[u] = h[u];
        for (auto p : g[u]){
            int v = p.v, i = p.id;
            bool chieu = p.chieu;
            if (v == pa) continue;
//            cout << u << " " << v << '\n';
            if (!chieu){
                tongin += E[i].second;
                h[v] = h[u] + E[i].second;
//                cout << E[i].second << '\n';
            }else{
                tongin += E[i].first;
                h[v] = h[u] + E[i].first;
//                cout << E[i].first << '\n';
            }
            pre_dfs_hld(v, u);
//            cout << v << " " << tongin << '\n';
            max_h[u] = max(max_h[u], max_h[v]);
        }
    }
    void dfs_reset(int u, int p){
        for (auto &pa : g[u]){
            int v = pa.v;
            if (v == p) continue;
//            cout << u << " " << v << '\n';
            int i = pa.id;
            if (pa.chieu == false){
                swap(E[i].first, E[i].second);
            }
            dfs_reset(v, u);
        }
    }
    void hld(int u,int len,int pa){
        int mx_child = -1;
        int down = -1;
        for (auto p : g[u]){
            int v = p.v, id = p.id;
            bool chieu = p.chieu;
            if (v == pa) continue;
            if (max_h[u] == max_h[v]){
                mx_child = v;
                if (!chieu){
                    down = E[id].second;
                }else{
                    down = E[id].first;
                }
            }
        }
        if (mx_child == -1){
            lens.pb(len);
            return;
        }
        hld(mx_child,len + down,u);
        for (auto p : g[u]){
            int v = p.v, i = p.id;
            bool chieu = p.chieu;
            int sum;
            if (!chieu){
                sum = E[i].second;
            }else{
                sum = E[i].first;
            }
            if (v == mx_child || v == pa) continue;
            hld(v , sum ,u);
        }
    }

    pair<int,int> trace[mx];

    void dfs(int u, int p){
        dp[u].first = h1[u];
        trace[u].first = u;
        for (auto pa : g[u]){
            int v = pa.v;
            if (v == p) continue;
            int id = pa.id;
            dfs(v, u);
            if (dp[u].first < dp[v].first){
                dp[u].second = dp[u].first;
                dp[u].first = dp[v].first;
                trace[u].second = trace[u].first;
                trace[u].first = trace[v].first;
            }else{
                if (dp[u].second < dp[v].first){
                    dp[u].second = dp[v].first;
                    trace[u].second = trace[v].first;
                }
            }
        }
    }
    int res[mx];
    void solve(){
        pre_dfs(1, 1);
        dfs(1, 1);
        int d1, d2;
        int mx2 = inf;
        int mx1 = inf;
        int h1tong = 0;
        int tong = 0;
        for (int i = 1; i <= n; i++){
            h1tong += E[i].first;
        }
        for (int i = 1; i <= n; i++){
            mx1 = min(mx1, h1tong - h1[i] + h0[i]);
        }

        for (int i = 1; i <= n; i++){
            if (mx2 > h1tong + h1[i] + h0[i] - dp[i].first - dp[i].second){
                d1 = trace[i].first;
            }
            mx2 = min(mx2, h1tong + h1[i] + h0[i] - dp[i].first - dp[i].second);
        }
        dfs_reset(1, 1);
        pre_dfs_hld(d1, d1);
        hld(d1, 0, d1);
//        cout << tongin << '\n';
        for (int i = 2; i - 2 < lens.size(); i++){
            res[i] = res[i - 1] + lens[i - 2];
        }
        for (int i = 1; i <= q; i++){
            int t;
            cin >> t;
            if (t == 1){
                cout << mx1 << '\n';
            }else{
                if (t - 1 > lens.size()){
                    cout << 0 << '\n';
                    continue;
                }
                cout << tongin - res[t] << '\n';
    //            cout << dp[2].first << '\n';
            }
        }
    }
}

void solve(){
//    if (dak::valid()){
//        dak::solve();
//    }else{
        mim::solve();
//    }
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

