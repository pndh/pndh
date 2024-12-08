#include "bits/stdc++.h"
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define ll long long
const int maxn = 5e5+5;
const int mod = 1e9+7;

struct SegTree{
	ll mx[4*maxn], cnt[4*maxn];
	void update(int id,  int l, int r , int pos ,int dp, int c){
		if(l>pos||r<pos)return;
		if(l==r){
			if(mx[id]==dp){
				cnt[id]+=c;
			}
			else if(mx[id]<dp)mx[id]= dp, cnt[id] =c;
			return;
		}
		int mid = (l+r)/2;
		update(2*id,l,mid,pos,dp,c);
		update(2*id+1,mid+1,r,pos,dp,c);
		if(mx[2*id]==mx[2*id+1]){
			mx[id]= mx[2*id];
			cnt[id]= (cnt[2*id]+cnt[2*id+1])%mod;
		}
		else if(mx[2*id]>mx[2*id+1]){
			mx[id]= mx[2*id];
			cnt[id]= cnt[2*id];
		}
		else {
			mx[id]= mx[2*id+1];
			cnt[id] = cnt[2*id+1];
		}
	}
	pair<int, ll> get(int id, int l, int r, int t_r){
		if(l>t_r)return {0,0};
		if(r<=t_r)return {mx[id], cnt[id]};
		int mid=(l+r)/2;
		pair<int,ll> lgt= get(2*id,l,mid,t_r);
		pair<int,ll> rgt = get(2*id+1,mid+1,r,t_r);
		if(lgt.fi==rgt.fi){
			return {lgt.fi, (lgt.se+rgt.se)%mod};
		}
		else if(lgt.fi>rgt.fi){
			return lgt;
		}
		else return rgt;

	}
}st;

int n, a[maxn];
pair<int,int> pr[maxn];
void compress(){
	for(int i =1;i<=n;i++){
		pr[i] = {a[i],i};
	}
	sort(pr+1,pr+n+1);
	int dem=1;
	for(int i=1;i<=n;i++){
		if(i>1){
			if(pr[i-1].first<pr[i].first)dem++;
		}
		a[pr[i].second] = dem;
	}
}

int dp[maxn];
ll cnt[maxn];

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	if(fopen("clis.INP","r")){
		freopen("clis.INP", "r", stdin);
		freopen("clistrau.OUT", "w", stdout);
	}
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	compress();

	for(int i=1;i<=n;i++){
		dp[i]= cnt[i]=1;
		pair<int, ll> x= st.get(1,1,n,a[i]-1);
		if(dp[i]< x.fi+1){
			dp[i]= x.fi+1; 	cnt[i]= x.se;
		}
		st.update(1,1,n,a[i], dp[i], cnt[i]);
	}
	ll ans=0,res=0;
	for(int i=1;i<=n;i++){
		if(ans<dp[i]){
			ans= dp[i], res= cnt[i];
		}
		else if(ans == dp[i]){
			res+= cnt[i];
			res%=mod;
		}
	}
	// cerr<<ans;
	cout<<res;
	return 0;
}
