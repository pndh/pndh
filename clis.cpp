#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 5e5 + 5;
int n, m;
int a[mx];
const int mod = 1e9 + 7;
void read(){

}

struct node{
    int cnt, dp;
};
struct Segtree{
    vector<node> seg;

    void init(int n){
        node a; a.cnt = a.dp = 0;
        seg.resize(8 * n + 2, a);
    }

    node mer(node a, node b){
        node c;
//        cout << 'w';
        if (a.dp == b.dp){
            c.dp = a.dp;
            c.cnt = a.cnt + b.cnt;
            c.cnt %= mod;
        }else{
            if (a.dp > b.dp){
                c = a;
            }else{
                c = b;
            }
        }
        return c;
    }

    void update(int l, int r, int x, int cnt, int dp, int id){
//        cout << l << " " << r << '\n';
        if (l == r && r == x){
            node a; a.cnt = cnt, a.dp = dp;
            seg[id] = mer(seg[id], a);
            return;
        }else if (l > x || r < x){
            return;
        }else{
            int mid = (l + r)/2;
            update(l, mid, x, cnt, dp, 2 *id);
            update(mid + 1, r, x, cnt, dp, 2 * id + 1);
            seg[id] = mer(seg[2 * id], seg[2 * id + 1]);
        }
    }

    node get(int l, int r, int x, int y, int id){
        if (x <= l && r <= y){
            return seg[id];
        }else if (l > y || r < x){
            node a; a.cnt = 0, a.dp = -1;
            return a;
        }else{
            int mid = (l + r)/2;
            return mer(get(l, mid, x, y, 2 * id), get(mid + 1, r, x, y, 2 * id + 1));
        }
    }
};

void solve(){
    cin >> n;
    vector<int> vect;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        vect.pb(a[i]);
    }
    vect.pb(-inf);
    sort(vect.begin(), vect.end());
    vect.erase(unique(vect.begin(), vect.end()), vect.end());
    for (int i = 1; i <= n; i++){
        a[i] = lower_bound(vect.begin(),vect.end(), a[i]) - vect.begin() + 1;
    }
    int sz = vect.size();
    Segtree seg;
    seg.init(sz);
    seg.update(1, sz, 1, 1, 1, 1);
    int mx_len = 1;
    int res = 0;
    for (int i = 1; i <= n; i++){
        node aa = seg.get(1, sz, 1, a[i] - 1, 1);
        if (aa.dp + 1 > mx_len){
            mx_len = aa.dp + 1;
            res = aa.cnt;
        }else if (aa.dp + 1 == mx_len){
            res += aa.cnt;
            res %= mod;
        }
        seg.update(1, sz, a[i], aa.cnt, aa.dp + 1, 1);
    }

    cout << res;
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
