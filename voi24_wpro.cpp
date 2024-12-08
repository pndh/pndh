#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pb push_back
int n,l1 ,l2 , m, c, d;
const int mx=1e6+5;
const __int128 inf=2e18;
int s[mx];
int dp[mx];
__int128 xx,yy;
int g;
int gcd(int a, int b, __int128& x, __int128& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    __int128 x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, __int128 &x0, __int128 &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    x0= (__int128)x0 * c/g;
    y0= (__int128)y0 * c/g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
void read(){
    cin >> n >> l1 >> l2 >> c >> d;
    if (l1<l2) swap (l1,l2);
    for (int i=1;i<=n;i++){
        int a;
        cin >> a;
        s[i]=s[i-1]+a;
    }
}
int cost (int len){
    if (len%g!=0){
        return inf;
    }
    int p=len/g;
    __int128 y=(__int128)yy*p;
    int inc=l1/g;
    // cout << y << " " << len << " " << inc << '\n';
    if (y>0){
        y=y%inc;
    }else{
        y=(inc-((0-y)%inc))%inc;
    }
    __int128 x=(len-y*l2)/l1;
    if (x<0){
        return inf;
    }
    return (__int128)(x+y);
}
int prod(__int128 a,__int128 b){
    if (inf/b < a){
        return inf;
    }else{
        return (__int128)a*b;
    }
}

void solve(){
    find_any_solution(l1,l2,__gcd(l1,l2),xx,yy,g);
    for (int i=1;i<=n;i++){
        dp[i]=inf;
    }
    for (int i=1;i<=n;i++){
        for (int j=0;j<i;j++){
            dp[i]=min(dp[i],dp[j]+prod((i-j-1),d)+prod((cost(s[i]-s[j])-1),c));
            if (dp[i]>inf){
                dp[i]=inf;
            }
        }
    }
    cout << dp[n];
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("wpro.inp","r",stdin);
    freopen("wpro.out","w",stdout);
    read();
    solve();
    return 0;
}