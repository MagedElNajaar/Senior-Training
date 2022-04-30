//https://vjudge.net/contest/490713#problem/O
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp,num,(n)*sizeof dp[0]);
const int N = 1e5 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int S[N], P[N], B[N], D[N], sorted[N];
int n, days;
#define M first
#define C second
typedef pair<ll, ll> seg;

extern struct node *Empty;

struct node {
    seg line;
    node *lf, *rt;

    node() {
        line = {0, 0};
        rt = lf = this;
    }

    node(const seg &l) {
        line = l;
        lf = rt = Empty;
    }
};

node *Empty = new node();

double intersect(const seg &l1, const seg &l2) {
    return (l2.C - l1.C) / (l1.M - l2.M - 0.0);
}

bool usefull(const seg &l1, const seg &l2, const seg &l3) {
    double d12 = intersect(l1, l2);
    double d23 = intersect(l2, l3);
    return d12 < d23;
}

ll subs(const seg &s, ll x) {
    return s.M * x + s.C;
}

void insert(seg ln, node *&cur, int ns = 0, int ne = days + 1) {
    if (cur == Empty) cur = new node(ln);
    double ip = intersect(ln, cur->line);
    if (ln.M == cur->line.M or ip < ns or ip > ne or ns == ne) {
        if (subs(ln, ns) > subs(cur->line, ns)) cur->line = ln;
        return;
    }
    int mid = ns + (ne - ns) / 2;
    if (ip > mid) {
        if (subs(ln, ns) > subs(cur->line, ns)) swap(cur->line, ln);
        insert(ln, cur->rt, mid + 1, ne);
    } else {
        if (subs(ln, ne) > subs(cur->line, ne)) swap(cur->line, ln);
        insert(ln, cur->lf, ns, mid);
    }
}

ll get(ll x, node *&cur, int ns = 0, int ne = days + 1) {
    if (x < ns or x > ne) return 0;
    ll ret = subs(cur->line, x);
    if (ns == ne) return ret;
    int mid = ns + (ne - ns) / 2;
    return max({ret, get(x, cur->lf, ns, mid), get(x, cur->rt, mid + 1, ne)});
}

ll solve() { //day index
    node *root = Empty;
    ll ret = 0;
    for (int ii = 0; ii <= n + 1; ii++) {
        int i = sorted[ii];
        ret = get(D[i], root);

        if (ret >= B[i]) {
            ll m = P[i];
            ll c = ret + S[i] - B[i] + (-D[i] - 1ll) * P[i];

            insert(make_pair(m,c),root);
        }
    }
    return ret;
}

int main() {
    int t = 0;
    while (scanf("%d%d%d", &n, &S[0], &days), n or S[0] or days) {
        D[n + 1] = days + 1;
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", D + i, B + i, S + i, P + i), sorted[i] = i;
        sorted[n + 1] = n + 1;
        sort(sorted, sorted + n + 1, [](int a, int b) { return D[a] < D[b]; });
        printf("Case %d: %lld\n", ++t, solve());
    }
    return 0;
}
