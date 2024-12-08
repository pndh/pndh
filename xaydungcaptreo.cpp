#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, g, k;
const int mx=2e3+5;
const int inf=1e18;
vector<int> dp_before, dp_cur;
int pre[mx];
int pre2[mx];
int val[mx];
int C(int i, int j){
    int mid;
    if (k==2){
        mid = round((double)(pre[j] - pre[i-1]) / (double)(j - i + 1));
        
        return mid * mid * (j-i + 1) + pre2[j] - pre2[i-1] - 2 * mid * (pre[j] - pre[i-1]);
    }else{
        mid = val[(i+j)/2];
        int midle = (i+j)/2;
        return mid * (midle - i) - (pre[midle-1] - pre[i-1]) + pre[j] - pre[midle-1] - mid * (j-midle+1);
    }
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {inf, -1};

    for (int t = optl; t <= min(mid, optr); t++) {
        best = min(best, {dp_before[t - 1] + C(t, mid), t});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;
    compute(l, mid - 1, optl, opt); 
    compute(mid + 1, r, opt, optr);
}


void read(){
    cin >> n >> g >> k;
    for (int i=1;i <=n; i++){
        cin >> val[i];
        pre[i] = pre[i-1] + val[i];
        pre2[i]= pre2[i-1] + val[i] * val[i];
    }
}

void solve() {
    dp_before.assign(n+5,0);
    dp_cur.assign(n+5,0);
    for (int i = 1; i <= n; i++) dp_before[i] = C(1, i);
    for (int i = 2; i <= g; i++) {
        compute(1, n , 1, n );
        dp_before = dp_cur;
    }
    cout << dp_before[n];
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}