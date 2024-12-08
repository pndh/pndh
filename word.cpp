#include<bits/stdc++.h>
#define pb push_back
#define task "word"
using namespace std;
const int mx = 2e5 + 5;
int n, m;

namespace sub1{
    int k, m;
    bool check(int n){
        if (n <= 1005) return true;
        return false;
    }
    int a[mx];
    bool good[7][1005];
    bool bad[7][1005];
    int dau[7][7];
    bool bang[1005][1005];
    bool vs[1005][1005];

    void sinh(int u, int len){
        if (len > m) return;
        if (vs[u][len]) return;
        vs[u][len] = true;
        if (bang[u][n + 1]){
                good[a[u]][len] =true;
                for (int i = 1;i <= n; i++){
                    if (bang[u][i]) sinh(i, len + 1);
                }
        }else{
                bad[a[u]][len] = true;
                for (int i = 1; i <= n; i++){
                    if (bang[u][i]) sinh(i, len + 1);
                }
        }
    }

    int res = 0;

    int dp[1005][7][1005];

    void dfs(int len, int sum, int pre, int hop){
        if (len > m) return;
        if (sum <= dp[len][pre][hop] && len > 0) return;
        dp[len][pre][hop] = sum;
        res = max(res, sum * hop);
        for (int i = 1; i <= 6; i++){
            for (int nx = 1; nx <= min(k, m - len); nx++){
                if (good[i][nx]){
                    int nx_hop = 0;
                    if (dau[pre][i]) nx_hop = 1;
                    int nx_sum = (2 * k - nx + 1) * nx / 2;
                    dfs(len + nx, sum + nx_sum, i, hop + nx_hop);
                }else{
                    if (bad[i][nx]){
                        int nx_sum = (2 * k - nx + 1) * nx / 2;
                        res = max(res, (sum + nx_sum) * hop);
                    }
                }
            }
        }
    }

    void solve(int n){
//        cout << n << '\n';
        cin >> k >> m;
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }

        for (int i = 1; i <= 6; i++){
            for (int j = 1; j <= 6; j++){
                int x; cin >> x;
                if (x == 1) dau[i][j] = true;
            }
        }

        for (int i = 1; i <= n + 1; i++){
            for (int j = 1; j <= n + 1; j++){
                int x;
                cin >> x;
                if (x == 1) bang[i][j] = true;
            }
        }

        for (int i = 1; i <= n; i++){
            if (bang[n + 1][i]) sinh(i, 1);
        }

        dfs(0, 0, 0, 0);
        cout << res;
    }
}
void read(){
    cin >> n;

    if (sub1 :: check(n)){
        sub1 :: solve(n);
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
