//https://vjudge.net/problem/SPOJ-PT07X
#include <bits/stdc++.h>

using namespace std;

#define neig(u, e, v) for(int e=head[u],v;~e and (v = to[e],1);e = nxt[e])
const int N = 1e5 + 9, M = 2 * N;
int head[N], to[M], nxt[M], n, ne;
int memo[N];

void init() {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}

void addEdge(int f, int t) {
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
}

void addBiEdge(int f, int t) {
    addEdge(f, t);
    addEdge(t, f);
}

int solve(int u, int p) {
    int &ret = memo[u];
    if (~ret) return ret;
    int c1 = 1, c2 = 0;
    neig(u, e1, v) {
        if (v == p) continue;
        c2++;
        c1 += solve(v, u);
        neig(v, e2, w) {
            if (w == u) continue;
            c2 += solve(w, v);
        }
    }
    return ret = min(c1, c2);
}


int main() {
    cin >> n;
    init();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addBiEdge(--u, --v);
    }
    memset(memo, -1, n * sizeof memo[0]);
    cout << solve(0, -1) << "\n";
    return 0;
}
