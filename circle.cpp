#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int k, n;
const int mx=1e6+5;
const int inf=1e18;
void read(){
    cin >> k >> n;
}

void solve(){
    int sum=0;
    int flag=true;
    for (int i=1;i<=n;i++){
        int a;
        char b;
        cin >> a >> b;
        if (!flag) continue;
        sum+=a;
        if (sum>210ll){
            cout << k;
            flag=false;
        }else{
            if (b=='T'){
                k++;
                if (k>8){
                    k=1;
                }
            }
        }
    }
    if (flag){
        cout << k;
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("circle.inp","r",stdin);
    freopen("circle.out","w",stdout);
    read();
    solve();
    return 0;
}