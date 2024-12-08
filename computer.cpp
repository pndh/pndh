#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
vector<int> g[mx];
bool vs[mx];
int timefi[mx];
void dfstimefi(int u,int pa){
    if (vs[u]){
        return;
    }
    vs[u]=true;
    vector<int> vect;
    for (auto x:g[u]){
        if (x==pa) continue;
        if (vs[x]) continue;
        dfstimefi(x,u);
        vect.pb(timefi[x]);
    }
    sort(vect.begin(),vect.end());
    reverse(vect.begin(),vect.end());
    for (int i=0;i<vect.size();i++){
        timefi[u]=max(vect[i]+i+1,timefi[u]);
    }
}
void read(){
    cin >> n;
}

void solve(){
    int a,b;
    cin >> a >> b;
    for (int i=1;i<n;i++){
        int x,y;
        cin >> x >>y;
        g[x].pb(y);
        g[y].pb(x);
    }
    vs[b]=true;
    dfstimefi(a,0);
    vs[b]=false;
    dfstimefi(b,0);
    int res1=max(timefi[a],timefi[b]);
    for (int i=1;i<=n;i++){
        vs[i]=false;
        timefi[i]=0;
    }
    vs[a]=true;
    dfstimefi(b,0);
    vs[a]=false;
    dfstimefi(a,0);
    int res2=max(timefi[a],timefi[b]);
    cout << min(res1,res2);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("computer.inp","r",stdin);
    freopen("computer.out","w",stdout);
    read();
    solve();
    return 0;
}