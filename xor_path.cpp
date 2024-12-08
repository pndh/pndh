#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define task "task"
using namespace std;
const int inf = 1e18;
const int mx = 2e5 + 5;
int n, m, k;
int bang[25][25];
map<int,int> mp[25][25];
vector<int> dx = {1, 0};
vector<int> dy = {0, 1};
vector<int> drx = {-1, 0};
vector<int> dry = {0, -1};
void read(){
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> bang[i][j];
        }
    }
}

int cnt = 0;

void solve(){
    if (n == 1 && m == 1){
        if (bang[1][1] == k) cout << 1;
        else cout << 0;
        return;
    }
    queue<pair<pair<int,int>,pair<int,int>>> q;
    q.push({{1, 1}, {0, 0}});
    int len = (n + m - 1)/2;
    while (!q.empty()){
        int x = q.front().first.first, y = q.front().first.second, val = q.front().second.first, dis = q.front().second.second;
        q.pop();
        val^= bang[x][y];
        dis++;
//        cout << dis << " " << len << '\n';
        if (dis == len){
            mp[x][y][val] ++;
            continue;
        }
        else{
            for (int t = 0; t < 2; t++){
                if (x + dx[t] <= n && y + dy[t] <= m){
                    q.push({{x + dx[t], y + dy[t]}, {val, dis}});
                }
            }
        }
    }
    q.push({{n, m}, {0, 0}});
    int lenr = (n + m - 1) - len;
    int res = 0;
//    cout << '\n';
    while (!q.empty()){
        int x = q.front().first.first, y = q.front().first.second, val = q.front().second.first, dis = q.front().second.second;
        q.pop();
        val^= bang[x][y];
//        cout << x << " " << y << '\n';
        dis++;
        if (dis == lenr){
            int xo = (val ^ k);
            res += mp[x - 1][y][xo] + mp[x][y - 1][xo];
            continue;
        }else{
            for (int t = 0; t < 2; t++){
                if (x + drx[t] > 0 && y + dry[t] > 0){
                    q.push({{x + drx[t], y + dry[t]}, {val, dis}});
                }
            }
        }
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
