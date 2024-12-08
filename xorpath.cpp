#include <bits/stdc++.h>
using namespace std; 
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC target("avx","sse2")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#define pb push_back
int n, m;
const int mx=2e5+5;
int q;
int st[mx];
int ed[mx];
int order[mx];
vector<int> g[mx];
int road[mx];
struct Trie{
    struct Node{
        Node* child[2];
        int cnt;
        set<int> st;
        Node() {
            for (int i = 0; i < 2; i++) child[i] = NULL;
            cnt = 0;

        }
    };

    int cur;
    Node* root;
    Trie() : cur(0) {
        root = new Node();
    };

    void add(int s,int ord) {
        Node* p = root;
        for (int i=30;i>=0;i--) {
            int c;
            if ((s>>i)&1){
                c=1;
            }else{
                c=0;
            }
            if (p->child[c] == NULL) p->child[c] = new Node();
            p = p->child[c];
            p->st.insert(ord);
        }
    }
    int get(int l,int r,int s){
        int sum=0;
        Node* p = root;
        for(int i=30;i>=0;i--){
            int c;
            if ((s>>i)&1){
                c=1;
            }else{
                c=0;
            }
            if (p->child[c^1]!=NULL){
                if (p->child[c^1]->st.lower_bound(l)!=p->child[c^1]->st.end() && *p->child[c^1]->st.lower_bound(l)<=r){
                    sum+=(1ll<<(i));
                    p=p->child[c^1];
                }else{
                    p=p->child[c];
                }
            }else{
                p=p->child[c];
            }
        }
        // cout << 't';
        return sum;
    }
};
vector<pair<bool,pair<int,int>>> qr;
void read(){
    cin >> q;
    int cnt=1;
    for (int i=1;i<=q;i++){
        string type;
        int x,y;
        cin >> type >> x >> y;
        if (type=="Add"){
            cnt++;
            g[x].pb(cnt);
            road[cnt]=road[x]^y;
            qr.pb({true,{cnt,road[cnt]}});
        }else{
            qr.pb({false,{x,y}});
        }
    }
}
int cc=1;
void dfs(int u){
    order[u]=cc;
    st[u]=cc;
    for (auto v:g[u]){
        cc++;
        dfs(v);
    }
    ed[u]=cc;
}
void solve(){
    dfs(1);
    Trie tri = Trie();
    tri.add(0,1);
    for (auto p:qr){
        if (p.first){
            tri.add(p.second.second,order[p.second.first]);
        }else{
            cout << tri.get(st[p.second.second],ed[p.second.second],road[p.second.first]) << '\n';
        }
    }    
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    read();
    solve();
    return 0;
}
