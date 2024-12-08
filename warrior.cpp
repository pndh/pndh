#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, m;
void read(){

}

void solve(){
    set<int> st;
    cin >> n;
    for (int i = 1; i <= n; i++){
        int x; cin >> x;

        while (st.find(x) != st.end()){
            st.erase(st.find(x));
            x = 2 * x;
        }
        st.insert(x);
        cout << *st.rbegin() << " ";
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
