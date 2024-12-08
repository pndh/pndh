#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, m;
int LG = 20;
void read(){
    cin >> n >> m;
    vector<int> us;
    int cur = 3;
    if (n <= 2){
        if (m == 2){
            cout << "1 OR 2" << '\n';
        }else{
            cout << "-1" << '\n';
        }
        return;
    }
    us.pb(1), us.pb(2);
    for (int i = 4; i <= n; i++){
        if (log2(i) != floor(log2(i))){
            cout << cur << " " << "OR" << " " << i << '\n';
            cur |= i;
        }else{
            us.pb(i);
        }
    }

    for (int j = 0; j < us.size(); j++){
        if (((1 << j) & cur) != ((1 << j) & m)){
            cout << us[j] << " " << "XOR" << " " << cur << '\n';
            cur ^= us[j];
        }else{
            cout << us[j] << " " << "OR" << " " << cur << '\n';
        }
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
    int t; cin >> t;
    while (t--){
        read();
        solve();
    }
}
