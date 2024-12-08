#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "impeval"
using namespace std;
const int inf = 1e18;
const int mx = 1e6 + 5;
int n, m, t;
int d1[mx], d2[mx];
int res[mx][2];
vector<pair<int,int>> edges;
vector<pair<int,int>> g[mx];
int bit[mx];
map<int,int> nen;
struct qry{
    int val1, val2, id, od, ex;
    bool operator<(const qry other){
        return val1 < other.val1;
    }
};
vector<qry> Q;
void update(int u, int p){
    int id = p;
    while (id < mx){
        bit[id] += u;
        id += (id & (-id));
    }
}

int getSum(int p){
    int id = p;
    int ans = 0;
    while (id > 0){
        ans += bit[id];
        id -= (id & (-id));
    }
    return ans;
}
void dijkstra(){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (int i = 1; i <= n; i++){
        d1[i] = inf, d2[i] = inf;
    }
    d1[1] = 0;
    d2[2] = 0;
    pq.push({0, 1});
    while (!pq.empty()){
        int u = pq.top().second;
        int dis = pq.top().first;
        pq.pop();
        for (auto p : g[u]){
            int v = p.first, d = p.second;
            if (d1[v] > d1[u] + d){
                d1[v] = d1[u] + d;
                pq.push({d1[v], v});
            }
        }
    }
    pq.push({0, 2});
    while (!pq.empty()){
        int u = pq.top().second;
        int dis = pq.top().first;
        pq.pop();
        for (auto p : g[u]){
            int v = p.first, d = p.second;
            if (d2[v] > d2[u] + d){
                d2[v] = d2[u] + d;
                pq.push({d2[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++){
        nen[d1[i]] = nen[d2[i]] = 0;
    }
}

bool cmp(int a,int b){
    if (d1[a] == d1[b]) return d2[a] < d2[b];
    return d1[a] < d1[b];
}

void read(){
    cin >> n >> m >> t;
    vector<int> adlist;
    for (int i = 1; i <= n; i++){
        adlist.pb(i);
    }
    for (int i = 1; i <= m; i++){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].pb({y, w});
        g[y].pb({x, w});
        edges.pb({x, y});
    }
    dijkstra();
    sort(adlist.begin(), adlist.end(), cmp);
    for (int i = 1; i <= t; i++){
        int a, w;
        cin >> a >> w;
        int x = edges[a - 1].first, y = edges[a - 1].second;
        int x1, x2, y1, y2, exx = 0, exy = 0;;
        if (d1[x] < d1[y]){
            x1 = d1[x];
            if ( d1[y] > d1[x] + w){
                exy = 1;
            }
            y1 = min(d1[y], d1[x] + w);
        }else{
            y1 = d1[y];
            if ( d1[x] > d1[y] + w){
                exx = 1;
            }
            x1 = min(d1[x], d1[y] + w);
        }

        if (d2[x] < d2[y]){
            x2 = d2[x], y2 = min(d2[y], d2[x] + w);
            if ( d2[y] > d2[x] + w){
                exy = 1;
            }
        }else{
            if ( d2[x] > d2[y] + w){
                exx = 1;
            }
            y2 = d2[y], x2 = min(d2[x], d2[y] + w);
        }
        nen[x1] = nen[x2] = nen[y1] = nen[y2] = 0;
        Q.pb({x1, x2, i, 0, exx});
        Q.pb({y1, y2, i, 1,exy});
    }
    int cnt = 0;
    for (auto &p : nen){
        cnt ++;
        p.second = cnt;
    }
    sort(Q.begin(), Q.end());
    int p = 0;
//    cout << d1[3] << '\n';
    for (auto q: Q){
        int v1 = q.val1, v2 = q.val2, id = q.id, od = q.od;
        while (p < adlist.size() && d1[adlist[p]] <= v1){
            update(1, nen[d2[adlist[p]]]);
            p++;
        }
        res[id][od] = getSum(nen[v2]) + q.ex;
    }
    for (int i = 1; i <= t; i++){
        cout << res[i][0] << " " << res[i][1] << '\n';
    }
}

void solve(){

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
