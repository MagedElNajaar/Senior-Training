//https://vjudge.net/contest/495975#problem/A

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int x[N], y[N], z[N], Qi[N], ans[N];
pair<int, int> edges[N];

struct DSU {
    int par[N];
    int sz[N];
    int n, numOfComp;
    struct Operation {
        int x, parX, y, szY;
    };
    stack<Operation> Op;
    int stkSz[N];
    int numOfJoins;

    void init(int n) {
        Op = stack<Operation>();
        numOfJoins = 0;
        this->n = n;
        numOfComp = n;
        fill(sz, sz + n, 1);
        iota(par, par + n, 0);
    }

    int find(int x) {
        if (par[x] == x)
            return x;
        Op.push({x, par[x], -1, -1});
        return par[x] = find(par[x]);
    }

    void join(int x, int y) {
        stkSz[numOfJoins++] = Op.size();
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        Op.push({x, par[x], y, sz[y]});
        par[x] = y;
        sz[y] += sz[x];
        numOfComp--;
    }

    void rollBack() {
        auto &op = Op.top();
        par[op.x] = op.parX;
        if (~op.y) {
            sz[op.y] = op.szY;
            numOfComp++;
        }
        Op.pop();
    }

    void rollBack(int numOfJoins) {
        int stkSz = this->stkSz[numOfJoins];
        while (Op.size() > stkSz) {
            rollBack();
        }
        this->numOfJoins = numOfJoins;
    }

    int getSz(int x, int y) {
        x = find(x);
        y = find(y);
        return x != y ? sz[x] + sz[y] : sz[x];
    }
} dsu;

void setSz(int mid) {
    if (dsu.numOfJoins > mid)
        dsu.rollBack(mid);
    else
        while (dsu.numOfJoins < mid)
            dsu.join(edges[dsu.numOfJoins].first, edges[dsu.numOfJoins].second);
}

void binarySearch(int st, int ed, int qs, int qe) {
    if (st == ed) {
        for (int i = qs; i <= qe; i++)
            ans[Qi[i]] = st;
        return;
    }
    int mid = st + (ed - st) / 2;
    setSz(mid);
    int m = partition(Qi + qs, Qi + qe + 1, [](int q) { return dsu.getSz(x[q], y[q]) >= z[q]; }) - Qi;

    binarySearch(st, mid, qs, m - 1);
    binarySearch(mid + 1, ed, m, qe);
    
}

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d%d", &edges[i].first, &edges[i].second);
    scanf("%d", &q);
    dsu.init(n + 1);
    for (int i = 0; i < q; i++) {
        scanf("%d%d%d", x + i, y + i, z + i);
        Qi[i] = i;
    }
    binarySearch(0, m, 0, q - 1);
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
