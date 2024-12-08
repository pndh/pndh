#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
int base = 11;
const int mod = 1e9 + 7;
int po[mx];
void read(){

}
int hashl[mx];
int getcode(int l, int r){
    return (hashl[r] - hashl[l-1] * po[ r-l+1 ] + mod*mod) % mod;
}
void solve(){
    cin >> n;
    po[0] = 1;
    for (int i=1;i <= n; i++){
        int a; cin >> a;
        po[i] = (po[i-1] * base)  % mod ; 
        hashl[i] = (hashl[i-1] * base + a) % mod;
    }
    for (int i=1;i <= n; i++ ){
        bool flag=true;
        int last=0;
        for (int j=1;j + i - 1 <= n ;j+=i){
            if (getcode(j, j+i-1) != getcode(1,i)){
                flag= false;
                break;
            }
            last=j;
        }
        if (!flag) continue;
        int len=n- last - i + 1;
        if (getcode(last+i,n) == getcode(1, len)){
            cout << i;
            break;
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}