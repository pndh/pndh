#include<bits/stdc++.h>
#define pb push_back
#define task "task"
using namespace std;
const int mx = 2e6 + 5;
int n, m, k;
int cntxor[mx];
int xxor[mx];
long long res = 0;
long long ans[mx];
void rev(int idx){
    int j = (xxor[idx] ^ k);
    cntxor[xxor[idx]] --;
    res -= cntxor[j];
}
void add(int idx){
    int j = (xxor[idx] ^ k);
    res += cntxor[j];
    cntxor[xxor[idx]] ++;
}

int block_size = 300;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
    }
};

void mo_s_algorithm(vector<Query> Q) {
    sort(Q.begin(), Q.end());
    for (int i = Q[0].l; i <= Q[0].r; i++){
        add(i);
    }
    int cur_l =Q[0].l, cur_r = Q[0].r;
    ans[Q[0].idx] = res;
    for (int i = 1; i < Q.size(); i++) {
        Query q = Q[i];
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            rev(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            rev(cur_r);
            cur_r--;
        }
        ans[q.idx] = res;
    }
}


void read(){
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++){
        int x; cin >> x;
        xxor[i] = (xxor[i - 1] ^ x);
    }
    vector<Query> vect;
    for (int i = 1; i <= m; i++){
        Query q;
        cin >> q.l >> q.r;
        q.l --;
        q.idx = i;
        vect.pb(q);
    }
    mo_s_algorithm(vect);
    for (int i = 1; i <= m; i++){
        cout << ans[i] << '\n';
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
    read();
    solve();
}
