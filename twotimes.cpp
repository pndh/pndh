#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, q;
const int mx=5e5+5;
const int inf=1e18;
int block=4;
int val[mx];
int bang[5005][5005];
struct query{
    int id,l,r;
};
vector<query> vect;
vector<int> nen;
bool compare(query a,query b){
    if (abs(a.l-b.l)+abs(a.r-b.r)<=block){
        return true;
    }else{
        return false;
    }
}
void read(){
    cin >> n >> q;
    for (int i=1;i<=n;i++){
        cin >> val[i];
        nen.pb(val[i]);
    }
    sort(nen.begin(),nen.end());
    for (int i=1;i<=q;i++){
        query qr;
        cin >> qr.l >> qr.r;
        qr.id=i;
        vect.pb(qr);
    }
    
}

void sub1(){
    // int id=lower_bound(val,val+n,1)-val;
    for (int i=1;i<=n;i++){
        int id=lower_bound(nen.begin(),nen.end(),val[i])-nen.begin();
        id++;
        for (int j=1;j<=n;j++){
            bang[i][j]=bang[i-1][j];
        }
        bang[i][id]++;
    }
    for (auto x:vect){
        int l=x.l,r=x.r;
        int cnt=0;
        for (int j=1;j<=n;j++){
            if (bang[r][j]-bang[l-1][j]==2){
                cnt++;
            }
        }
        cout << cnt << '\n';
    }
}

void sub2(){

}

void solve(){
    sub1();
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("twotimes.inp","r",stdin);
    freopen("twotimes.out","w",stdout);
    read();
    solve();
    return 0;
}