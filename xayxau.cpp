#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n, m;
const int mx=1e6+5;
const int inf=1e18;
int dp[205][205][205];
void read(){

}

void solve(){
    string a,b;
    cin >> a >> b;
    int sa = a.size(),sb = b.size();
    a = ' ' + a;
    b = ' ' + b;
    for (int i=0; i<= sa; i++ ){
        for (int j=0;j <= sb; j++ ){
            for (int deg=0 ; deg <= 200; deg++){
                dp[i][j][deg] = inf;
            }
        }
    }
    dp[0][0][0] = 0;
    // cout << dp[1][0][2] << " " << sa << " " << sb << '\n';
    for (int i=0;i <= sa; i++){
        for (int j=0; j <= sb ;j++){
            for (int deg=0;deg <= 200; deg++){
                if (deg > 0 ){
                    int prei = i,prej= j;
                    if (a[i] == '(') prei --;
                    if (b[j] == '(') prej --;
                    dp[i][j][deg]=min(dp[i][j][deg], dp[prei][prej][deg-1] + 1);
                    // cout << i << " " << j << " " << deg << "->" << " " << prei << " " << prej << " " << deg-1 << 'w' << '\n';
                }
                int prei = i, prej = j;
                if (a[i] == ')') prei--;
                if (b[j] == ')') prej--;
                assert(prei >= 0);
                assert(prej >= 0);
                dp[i][j][deg] = min(dp[i][j][deg], dp[prei][prej][deg+1] + 1);
                // cout << i << " " << j << " " << deg << "->" << " " << prei << " " << prej << " " << deg+1 << 'p' << '\n';
            }
        }
    }
    for (int i=0;i <= sa; i++){
        for (int j=0; j <= sb ;j++){
            for (int deg=0;deg <= 200; deg++){
                if (deg > 0 ){
                    int prei = i,prej= j;
                    if (a[i] == '(') prei --;
                    if (b[j] == '(') prej --;
                    dp[i][j][deg]=min(dp[i][j][deg], dp[prei][prej][deg-1] + 1);
                    // cout << i << " " << j << " " << deg << "->" << " " << prei << " " << prej << " " << deg-1 << 'w' << '\n';
                }
                int prei = i, prej = j;
                if (a[i] == ')') prei--;
                if (b[j] == ')') prej--;
                assert(prei >= 0);
                assert(prej >= 0);
                dp[i][j][deg] = min(dp[i][j][deg], dp[prei][prej][deg+1] + 1);
                // cout << i << " " << j << " " << deg << "->" << " " << prei << " " << prej << " " << deg+1 << 'p' << '\n';
            }
        }
    }
    int cur=0;
    string r = "";
    while (dp[sa][sb][cur] > 0){
        // cout << sa << " " << sb << '\n';
        // cout << dp[sa][sb][cur] << '\n';
        if (cur > 0){
            int nexti=sa,nextj=sb;
            if (a[sa] == '(') nexti--;
            if (b[sb] == '(') nextj--;
            if (dp[nexti][nextj][cur-1]==dp[sa][sb][cur]-1){
                r+='(';
                cur--;
                sa=nexti,sb=nextj;
                continue;
            }
        }
        int nexti=sa,nextj=sb;
        if (a[sa] == ')') nexti--;
        if (b[sb] == ')') nextj--;
        if (dp[nexti][nextj][cur+1]==dp[sa][sb][cur]-1){
            r+=')';
            cur++;
            sa=nexti,sb=nextj;
        }
    }
    reverse(r.begin(),r.end());
    cout << r;
    // cout << dp[sa][sb][0];
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}