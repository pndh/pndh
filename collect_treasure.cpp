#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, m;
int bang[1005][1005];
int pref[1005][1005];
void read(){

}

void prepro(){
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + bang[i][j];
        }
    }
}

long long calc(int x1, int y1, int x2, int y2){
    return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
}

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            char c;
            cin >> c;
            bang[i][j] = c - '0';
        }
    }
    int q; cin >> q;
    prepro();
    for (int i = 1; i <= q; i++){
        int x, y, k;
        cin >> x >> y >> k;
        k -= bang[x][y];
        int res = 0;
        int prex1 = x, prey1 = y, prex2 = x, prey2 = y;
        for (int len = 0; len <= max(n, m); len++){
            int x1 = max(1ll, x - len);
            int y1 = max(1ll, y - len);
            int x2 = min(n, x + len);
            int y2 = min(m, y + len);
            if (k <= calc(x1, y1, x2, y2) - calc(prex1, prey1, prex2, prey2)){
                res += 2 * k * len;
                break;
            }else{
                k -= (calc(x1, y1, x2, y2) - calc(prex1, prey1, prex2, prey2));
                res += 2 * (calc(x1, y1, x2, y2) - calc(prex1, prey1, prex2, prey2)) * len;
            }
            prex1 = x1, prex2 = x2, prey1 = y1, prey2 = y2;
        }
        cout << res << '\n';
    }
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
