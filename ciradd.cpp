#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1000+5;
const int inf=1e18;
int dp[mx][mx];
int val[1005];
void read(){
    cin >> n;
}
int pre[mx];
void solve(){
    for (int i=1;i<=n;i++){
        cin >> val[i];
    }
    for (int i=n+1;i<=2*n;i++){
        val[i]=val[i-n];
    }
    for (int i=1;i<=2*n;i++){
        for (int j=i+1;j<=2*n;j++){
            dp[i][j]=inf;
        }
    }
    for (int i=1;i<=2*n;i++){
        pre[i] = val[i] + pre[i-1];
        dp[i][i] = 0;
    }
    for (int j=1;j<=2*n;j++){
        for (int i=j-1;i>=max(1ll,j-n+1);i--){
            for (int k=i;k < j; k++){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + pre[j] - pre[i-1]);
            }
        }
    }
    int res=inf;
    for (int i=1;i<n;i++){
        res = min(res,dp[i][i+n-1]);
    }
    cout << res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}