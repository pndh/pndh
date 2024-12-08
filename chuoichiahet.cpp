#include<bits/stdc++.h>
#define pb push_back
#define task "task"
using namespace std;
const int mx = 1e6;
int n, m;
int sang[mx + 5];
long long bcnn[mx];
void prepro(){
    bcnn[0] = 1;
    for (int i = 1; i <= 80; i++){
        bcnn[i] = (1ll * bcnn[i - 1] * i)/__gcd(bcnn[i - 1], i);
    }
}

void read(){
    cin >> n;
    prepro();
}

void solve(){
    for (int i = 1; i <= n; i++){
        int l, r, k;
        cin >> l >> r >> k;
        if (k >= 80) {cout << 0 << '\n'; continue;}
        int res = (r / bcnn[k]) - (l - 1)/ bcnn[k] - (r % bcnn[k] == 0) + ((l - 1) % bcnn[k] == 0);
        int bu = (r / bcnn[k + 1]) - (l - 1) / bcnn[k + 1] - (r % bcnn[k + 1] == 0) + ((l - 1) % bcnn[k + 1] == 0) ;
        cout <<(long long) res - bu << '\n';
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
