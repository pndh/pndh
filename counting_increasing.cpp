#include<bits/stdc++.h>
#define pb push_back
#define task "task"
using namespace std;
const int mx = 2e5 + 5;
int n, m;
vector<int> dp[mx];
const int mod = 1e9;
void read(){
    int n; cin >> n;
    dp[0].resize(2);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++){
        int sz = sqrt(i) + 10;
        dp[i].resize(sz);
        for (int j = 1; j <= sqrt(i); j++){
            dp[i][j] = (dp[i - j][j] + dp[i - j][j - 1]) % mod;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= sqrt(n); i++){
        ans += dp[n][i];
        ans %= mod;
    }
    cout << ans;
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
