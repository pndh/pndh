#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, k;
const int mx=1e6+5;
const int inf=1e18;
set<int> checker;
int child[mx];
const int mod=1e9+7;
bool vs[mx];
int goin[mx];
int c[mx];
// int adres[mx];
int res[mx];
void read(){
    cin >> n >> k;
    for (int i=1;i<=n;i++){
        int a;
        cin >> a;
        child[i]=a;
        goin[a]++;
        checker.insert(a);
    }
}
int calc(int u){
    if (k<2 && u>1){
        return 0;
    }
    if (u==0){
        return 0;
    }
    if (u==1){
        return k;
    }
    int dp[u+10][2];
    dp[1][1]=1;
    dp[1][0]=0;
    for (int i=2;i<=u;i++){
        dp[i][1]=dp[i-1][0];
        dp[i][0]=dp[i-1][1]*(k-1)+dp[i-1][0]*(k-2);
        // cout << dp[i][1] << '\n';
        dp[i][0]%=mod;
        dp[i][1]%=mod;
    }
    dp[u][0]*=k;
    dp[u][0]%=mod;
    // cout << dp[u][0] << '\n';
    return dp[u][0];
}
int sz=0;
int cnt=0;
void dfs(int u){
    if (vs[u]) return;
    sz++;
    vs[u]=true;
    dfs(child[u]);
}
// void dfsr(int u){
//     if (vs[u])
// }
void sub1(){
    int res=1;
    for (int i=1;i<=n;i++){
        sz=0;
        if (!vs[i]){
            dfs(i);
            res*=calc(sz);
            res%=mod;
        }
    }
    cout << res;
}
void sub2(){
    queue<int> topo;
    int res=1;
    for (int i=1;i<=n;i++){
        if (goin[i]==0){
            topo.push(i);
        }
    }
    while(!topo.empty()){
        int u=topo.front();
        vs[u]=true;
        res*=(k-1);
        res%=mod;
        topo.pop();
        goin[child[u]]--;
        if (goin[child[u]]==0){
            topo.push(child[u]);
        }
    }
    // cout << res << '\n';
    for (int i=1;i<=n;i++){
        sz=0;
        if (!vs[i]){
            // cout << i << '\n';
            dfs(i);
            res*=calc(sz);
            res%=mod;
        }
    }
    cout << res;
}
void solve(){
    if (checker.size()==n){
        sub1();
    }else{
        sub2();
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("color.inp","r",stdin);
    freopen("color.out","w",stdout);
    read();
    solve();
    return 0;
}