#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
void read(){

}
vector<int> bang[1005];
void solve(){
    cin >> n >> m;

    set<pair<int,int>> st;
    for (int i=1; i<= n ;i++){
        for (int j=1; j <=m; j++){
            int a;
            cin >> a;
            bang[i].pb(a);
        }
        sort(bang[i].begin(),bang[i].end());
    }
    int res=inf;
    for (int j=0; j<m;j++){
        int mid=bang[1][j];
        int maxx=mid,minn = mid;
        for (int i=2; i<=n; i++){
            auto it =upper_bound(bang[i].begin(), bang[i].end(), mid);
            if (it==bang[i].begin()){
                minn=min(minn,*it);
                maxx=max(maxx,*it);
                // cout << mid << ":" << *it << "\n";
                continue;
            }
            it--;
            auto it2=it--;
            if (it==bang[i].end()){
                minn=min(minn,*it2);
                maxx=max(maxx,*it2);
                // cout << mid << ":" << *it2 << "\n";
                continue;
            }
            if (max(*it-minn,maxx-*it) > max(maxx - *it2,*it2-minn)){
                minn=min(minn,*it2);
                maxx=max(maxx,*it2);
                // cout << mid << ":" << *it2 << "\n";
            }else{
                maxx=max(maxx,*it);
                minn=min(minn,*it);
                // cout << mid << ":" << *it << "\n";
            }
        }
        res = min(res, maxx - minn);
    }
    cout << res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}