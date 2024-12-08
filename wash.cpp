#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m, q;
const int mx=1e6+5;
const int inf=1e18;
int bon[mx];
int res[mx];
set<pair<int,int>> st;
void read(){
    cin >> m >> n >> q;
    for (int i=1;i<=n;i++){
        int a;
        cin >> a;
        bon[a]=1;
    }
    int start=1;
    int len=0;
    for (int i=1;i<=m;i++){
        if (!bon[i]){
            len++;
        }else{
            st.insert({len,start*(-1)});
            len=0;
            cout << len << " " << start*(-1) << '\n';
            start=i+1;
        }
    }
    st.insert({len,start*(-1)});
    cout << len << " " << start*(-1) << '\n';
    vector<int> qr;
    for (int i=1;i<=q;i++){
        int a;
        cin >> a;
        qr.pb(a);
    }
    for (int j=n+1;j<=m;j++){
        pair<int,int> p=*st.rbegin();
        int len=p.first;
        int l1=p.second*(-1);
        int pos;
        int r2=len+l1-1;
        if (len%2==1){
            pos=l1+(len/2);
            res[n+1]=pos;
            int r1=pos-1;
            int l2=pos+1;
            auto it=st.end();
            it--;
            st.erase(it);
            st.insert({r1-l1+1,l1*(-1)});
            st.insert({r2-l2+1,l2*(-1)});
            // cout << r1-l1+1 << " " << l1*(-1) << '\n';
            // cout << r2-l2+1 << " " << l2*(-1) << '\n';
        }else{
            pos=l1+(len/2);
        }
    }
    for(auto x:qr){
        cout << res[x] << '\n';
    }
}

void solve(){
    
}

signed main(){
    // cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}