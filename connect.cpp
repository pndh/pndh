#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
bool bang[55][55];
void read(){

}

void solve(){
    cin >> n >> m;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            char c;
            cin >> c;
            if (c=='.') continue;
            bang[i][j]=true;
        }
    }
    int base=0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (!bang[i][j]) continue;
            if (bang[i-1][j]){
                base++;
            }
            if (bang[i-1][j-1]){
                base++;
            }
            if (bang[i-1][j+1]){
                base++;
            }
            if (bang[i][j-1]){
                base++;
            }
            if (bang[i][j+1]){
                base++;
            }
            if (bang[i+1][j-1]){
                base++;
            }
            if (bang[i+1][j]){
                base++;
            }
            if (bang[i+1][j+1]){
                base++;
            }
        }
    }
    base/=2;
    int res=0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (bang[i][j]) continue;
            int cnt=0;
            if (bang[i-1][j]){
                cnt++;
            }
            if (bang[i-1][j-1]){
                cnt++;
            }
            if (bang[i-1][j+1]){
                cnt++;
            }
            if (bang[i][j-1]){
                cnt++;
            }
            if (bang[i][j+1]){
                cnt++;
            }
            if (bang[i+1][j-1]){
                cnt++;
            }
            if (bang[i+1][j]){
                cnt++;
            }
            if (bang[i+1][j+1]){
                cnt++;
            }
            res=max(res,cnt);
        }
    }
    cout << base+res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("connect.inp","r",stdin);
    freopen("connect.out","w",stdout);
    read();
    solve();
    return 0;
}