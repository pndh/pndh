#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
int n, m;
const int mx=1e5+5;
const int inf=1e9;
void read(){

}
int a[mx][15];
int dp[mx][15][15];
void solve(){
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i][0];
    }
    for (int i=0;i<=n;i++){
        for (int j=0; j<=m; j++){
            for (int k=0; k<= m;k ++){
                dp[i][j][k] = -inf;
            }
        }
    }
    dp[0][0][0]=0;
    for (int i=1;i <=n; i++){
        int x;
        cin >> x;
        for (int j=1;j<=m;j++){
            a[i][j]=a[i][j-1]*x;
        }
    }
    for (int i=1;i <=n; i++){
        for (int j=0; j<=m; j++){
            for (int k=j; k>=0;k--){
                if (k == j){
                    dp[i][j][k] = max(dp[i][j][k], a[i][k]);
                }
                for (int t=m;t>=k;t--){
                    dp[i][j][k] = max(dp[i-1][j][t] + a[i][k], dp[i][j][k]);
                }
                for (int t=0;t<k;t++){
                    dp[i][j][k] = max(dp[i-1][j-(k-t)][t] + a[i][k], dp[i][j][k]);
                }
            }
        }
    }
    int res=-inf;
    for (int i=1; i<=n;i++){
        for (int j=0;j <=m; j++){
            for (int k=0; k <=m;k++){
                res = max(res,dp[i][j][k]);
            }
        }
    }
    cout << res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("watermelon.inp","r",stdin);
    freopen("watermelon.out","w",stdout);
    read();
    solve();
    return 0;
}