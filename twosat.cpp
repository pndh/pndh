#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
int base=8005;
vector<int> g[mx];
void read(){
    cin >> n >> m;
    for (int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        int adjx=-(x)+base,adjy=-(y)+base;
        x+=base,y+=base;
        g[adjy].pb(x);
        g[adjx].pb(y);
        // cout << adjx << " " << y << '\n';
        // cout << adjy << " " << x << '\n';
    }
}
int num[mx],low[mx];
bool val[mx];
bool vs[mx];
int adres[mx];
stack<int> st;
int cnt;
vector<int> snode[mx];
int res[mx];
int tim=0;
void dfs(int u){
    low[u]=num[u]=++tim;
    st.push(u);
    for (auto v:g[u]){
        if (vs[v]) continue;
        if (num[v]) {
            low[u]=min(num[v],low[u]);
        }else{
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
    }
    if (low[u]==num[u]){
        cnt++;
        int v=0;
        while(v!=u){
            v=st.top();
            st.pop();
            snode[cnt].pb(v);
            adres[v]=cnt;
            vs[v]=true;
        }
    }
}
void solve(){
    dfs(base+1);
    for (int i=1;i<=m;i++){
        if (num[i+base]==0){
            dfs(i+base);
        }
        if (num[base-i]==0){
            dfs(base-i);
        }
    }
    // for (int i=1;i<=cnt;i++){
    //     cout << i << " " << ":";
    //     for (auto v:snode[i]){
    //         cout << v << ' ';
    //     }
    //     cout << '\n';
    // }
    for (int i=1;i<=m;i++){
        if (adres[i+base]==adres[base-i]){
            cout << "NO";
            return;
        }
    }
    for (int i=cnt;i>=1;i--){
        bool flag=false;
        for (auto v:snode[i]){
            if (val[v]){
                // cout << i << " " << v << '\n';
                flag=true;
                break;
            }
        }
        if (!flag){
            for (auto v:snode[i]){
                v=-(v-base)+base;
                val[v]=true;
            }
        }else{
            for (auto v:snode[i]){
                val[v]=true;
            }
        }
    }
    cout << "YES" << '\n';
    int c=1;
    for (int i=1;i<=m;i++){
        if (val[i+base]){
            res[c]=i;
            c++;
        }
    }
    cout << c-1 << '\n';
    for (int i=1;i<c;i++){
        cout << res[i] << " ";
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}