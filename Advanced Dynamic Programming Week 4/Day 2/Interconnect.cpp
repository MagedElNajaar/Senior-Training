//https://vjudge.net/contest/490713#problem/P
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 30 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
ll dp[N][N];
map<vector<int>, double> mp;
int n;

ll solve(int rem, int mn) {
    if (rem == 0) return 1;
    ll &ret = dp[rem][mn];
    if (~ret) return ret;
    ret = 0;
    for (int i = mn; i <= rem; i++) {
        ret += solve(rem - i, i);
    }
    return ret;
}

double solve(vector<int> v) {

    if (v.size() == 1) return 0;
    auto &ret = mp.emplace(v, -1).first->second;
    if (ret != -1) return ret;
    ll sum = 0;
    double q = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            auto vv = v;
            vv[i] += vv[j];
            //vv.erase(vv.begin() + j);
            vv[j] = vv.back();
            vv.pop_back();
            sort(vv.begin(), vv.end());
            q += v[i] * v[j] / (n * (n - 1.0) / 2) * (1 + solve(vv));
        }
    }
    for (auto &it: v)
        sum += it * (it - 1) / 2;
    double p = sum / (n * (n - 1.0) / 2);
    //ret = q + p * (1 + ret)
    //ret = q + p + p*ret
    //ret - p * ret = q + p
    ret = (q + p) / (1 - p);
    return ret;
}


vector<vector<int>> adj;
int vis[N], vid;

int dfs(int u) {
    if (vis[u] == vid) return 0;
    vis[u] = vid;
    int ret = 1;
    for (auto &v: adj[u])
        ret += dfs(v);
    return ret;
}

int main() {
    int m;
    while (cin >> n >> m) {
        adj.clear();
        adj.resize(n);
        while (m--) {
            int a, b;
            cin >> a >> b;
            adj[--a].push_back(--b);
            adj[b].push_back(a);

        }
        vid++;
        vector<int> v;
        for (int i = 0; i < n; i++)
            if (vis[i] != vid)
                v.push_back(dfs(i));
        sort(v.begin(), v.end());
        cout << fixed << setprecision(9) << solve(v) << endl;
    }
    return 0;
}
