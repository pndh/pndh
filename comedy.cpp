#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
void read(){

}

void solve(){
    int mxv=0,mxid=0;
    for (int i=1;i<=5;i++){
        int sum=0;
        for (int j=1;j<=4;j++){
            int a;
            cin >> a;
            sum+=a;
        }
        if (sum>=mxv){
            mxv=sum;
            mxid=i;
        }
    }
    cout << mxid << " " << mxv;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("comedy.inp","r",stdin);
    freopen("comedy.out","w",stdout);
    read();
    solve();
    return 0;
}