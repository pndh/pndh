#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
int n, m;
const int mx=1e6+5;
const int mod =1e9+7;

int dp[2][10005];
void read(){
    cin >> n >> m;
}
int calc(int ni,int c){
    if (c<0) return 0;
    return dp[ni][c];
}
void solve(){
    for (int i=1;i<=n;i++){
        dp[0][0]=1;
        dp[1][0]=1;
        for (int j=1;j<=m;j++){
            dp[1][j]=calc(1,j-1)+calc(0,j)-calc(0,j-i);
            dp[1][j]+=mod*mod;
            dp[1][j]%=mod;
        }
        for (int j=1;j<=m;j++){
            dp[0][j]=dp[1][j];
        }
    }
    cout << dp[0][m];
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}