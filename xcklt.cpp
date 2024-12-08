#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int short
int n, m;
const int mx=100+5;
const int inf=16191;
short dp[mx][mx][mx];
struct tracer{
    char a;short i,j,k;
};
tracer trace[mx][mx][mx];
void read(){

}
void solve(){
    string a,b,c;
    cin >> a >> b >> c;
    int lena=a.size(),lenb=b.size(),lenc=c.size();
    a=' '+a;
    b=' '+b;
    c=' '+c;
    memset(dp, 0x3f, sizeof(dp));
    for (int i=0;i<=lena;i++){
        for (int j=0;j<=lenb;j++){
            for (int k=0;k<=lenc;k++){
                tracer other;
                other.a='&';
                trace[i][j][k]=other;
            }
        }
    }
    dp[0][0][0]=0;
    for (int i=0;i<=lena;i++){
        for (int j=0;j<=lenb;j++){
            for (int k=0;k<=lenc;k++){
                if (dp[i][j][k]<inf){
                    if (i<lena){
                        int nextj,nextk;
                        if (a[i+1]==b[j+1]){
                            nextj=j+1;
                        }else{
                            nextj=j;
                        }
                        if (a[i+1]==c[k+1]){
                            nextk=k+1;
                        }else{
                            nextk=k;
                        }
                        if (dp[i][j][k]+1<dp[i+1][nextj][nextk]){
                            dp[i+1][nextj][nextk]=dp[i][j][k]+1;
                            tracer t;
                            t.a=a[i+1];
                            t.i=i,t.j=j,t.k=k;
                            trace[i+1][nextj][nextk]=t;
                        }
                    }
                    if (j<lenb){
                        int nexti,nextk;
                        if (b[j+1]==a[i+1]){
                            nexti=i+1;
                        }else{
                            nexti=i;
                        }
                        if (b[j+1]==c[k+1]){
                            nextk=k+1;
                        }else{
                            nextk=k;
                        }
                        if (dp[i][j][k]+1<dp[nexti][j+1][nextk]){
                            dp[nexti][j+1][nextk]=dp[i][j][k]+1;
                            tracer t;
                            t.a=b[j+1];
                            t.i=i,t.j=j,t.k=k;
                            trace[nexti][j+1][nextk]=t;
                        }
                    }
                }
            }
        }
    }
    for (int k=0;k<=lenc;k++){
        if (dp[lena][lenb][k]!=inf){
            cout << dp[lena][lenb][k];
            string s="";
            int i=lena,j=lenb;
            cout << '\n';
            while(trace[i][j][k].a!='&'){
                s+=trace[i][j][k].a;
                int nexti=trace[i][j][k].i,nextj=trace[i][j][k].j,nextk=trace[i][j][k].k;
                i=nexti,j=nextj,k=nextk;
            }
            reverse(s.begin(),s.end());
            cout << s;
            return;
        }
    }
    cout << "TRETRAU";
    // cout << dp[1][0][0] << '\n';
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen("xcklt.inp","r",stdin);
    freopen("xcklt.out","w",stdout);
    read();
    solve();
    return 0;
}