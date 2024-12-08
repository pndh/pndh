#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
bool vs[mx];
map<int,int> mp;
int base=29;
const int mod=1e9+13;
void read(){

}
int getHash(string x){
    int code=0;
    for (int i=0;i<x.size();i++){
        code=code*base + (x[i] - 'a' +1)%mod;
    }
    return code;
}
int hashl[mx];
int po[mx];
int getcode(int l,int r){
    return ( hashl[r] - hashl[l-1] * po[r-l+1] + mod*mod )%mod;
}
void solve(){
    cin >> n >> m;
    string s;
    cin >> s;
    s=' ' + s;
    po[0]=1;
    for (int i=1;i<=n+5;i++){
        po[i] = po[i-1] * base;
        po[i]%=mod;
    }
    for (int i=1;i<=n;i++){
        hashl[i] = hashl[i-1]*base + ( s[i] - 'a' + 1);
        hashl[i] %= mod;
    }
    for (int i=1;i<=m;i++){
        string x;
        cin >> x;
        if (vs[x.size()]){
            cout << mp[getHash(x)] << '\n';
        }else{
            vs[x.size()] = true;
            int sz = x.size();
            for (int j=1;j+sz-1<=n;j++){
                mp[getcode(j,j+sz-1)]++;
            }
            cout << mp[getHash(x)] << '\n';
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}