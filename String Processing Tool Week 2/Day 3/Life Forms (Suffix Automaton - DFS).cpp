//https://vjudge.net/contest/489655#problem/D
#include <bits/stdc++.h>

#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7, OO = 0x3f3f3f3f;
const ll LOO = 0x3f3f3f3f3f3f3f3f;
const long double EPS = 1e-8;

#define arrRange(t, a, mn, mx) t a##_[mx-mn+1], *a=(a##_)-mn;
#define arrRange2D(t, a, mn, mx, d) typedef t _##a[d]; arrRange(_##a, a, mn, mx)

const int N = 1e6 + 5, ALPHA = 256;

int numOfNodes, lstNode;
arrRange(int, len, -1, N);
arrRange(int, fail, -1, N);
arrRange(unsigned char, str, -1, N);
arrRange2D(unsigned char, childChars, -1, N, ALPHA);
arrRange(int, childSz, -1, N);
arrRange2D(int, child, -1, N, ALPHA);

int addNode() {
    childSz[numOfNodes] = 0;
    memset(child[numOfNodes], -1, sizeof child[numOfNodes]);
    return numOfNodes++;
}

void init() {
    numOfNodes = lstNode = 0;
    addNode();
    len[0] = 0;
    fail[0] = -1;
    len[-1] = -1;
    memset(child[-1], 0, sizeof child[-1]);
    iota(childChars[-1], childChars[-1] + ALPHA, '\0');
    childSz[-1] = ALPHA;
}

void addEdge(int f, int t, unsigned char c) {
    child[f][c] = t;
    childChars[f][childSz[f]++] = c;
}

int parN[N];
unsigned char parC[N];

void addChar(unsigned char c) {
    int cur = addNode(), p;
    len[cur] = len[lstNode] + 1;
    parN[cur] = lstNode;
    parC[cur] = c;
    for (p = lstNode; !~child[p][c]; p = fail[p]) {
        addEdge(p, cur, c);
    }
    int q = child[p][c];
    if (len[p] + 1 == len[q]) fail[cur] = q;
    else {
        int clone = addNode();
        len[clone] = len[p] + 1;
        parN[clone] = p;
        parC[clone] = c;
        memcpy(child[clone], child[q], sizeof child[clone]);
        memcpy(childChars[clone], childChars[q], sizeof childChars[clone]);
        childSz[clone] = childSz[q];
        fail[clone] = fail[q];
        for (; ~p; p = fail[p]) {
            int &ch = child[p][c];
            if (ch != q) break;
            ch = clone;
        }
        fail[q] = fail[cur] = clone;
    }
    lstNode = cur;
}

void print() {
    for (int i = 0; i < numOfNodes; i++) {
        for (int k = 0; k < childSz[i]; k++) {
            unsigned char c = childChars[i][k];
            int j = child[i][c];
            printf("%d,%d %d,%d %c\n", i, len[i], j, len[j], c);
        }
        int j = fail[i];
        //printf("%d,%d %d,%d fail\n", i, len[i], j, len[j]);
    }
}

void build() {
    init();
    for (unsigned char *s = str; *s; s++) {
        addChar(*s);
    }
}

bitset<100> memo[N];
int vis[N], vid;

bitset<100> solve(int u) {
    auto &ret = memo[u];
    if (vis[u] == vid) return ret;
    vis[u] = vid;
    ret.reset();
    for (int k = 0; k < childSz[u]; k++) {
        unsigned char c = childChars[u][k];
        int v = child[u][c];
        if (c >= 128) ret[c - 128] = 1;
        else ret |= solve(v);
    }
    return ret;
}

void Print(int i) {
    if (i) {
        Print(parN[i]);
        printf("%c", parC[i]);
    }
}

int mx, n;

void dfs(int u) {
    if (vis[u] == vid) return;
    vis[u] = vid;
    sort(childChars[u], childChars[u] + childSz[u]);
    if (solve(u).count() > (n / 2)) if (mx == len[u]) Print(u), puts("");
    for (int k = 0; k < childSz[u]; k++) {
        unsigned char c = childChars[u][k];
        int v = child[u][c];
        dfs(v);
    }
}

int main() {
    FIO
    // freopen("input.txt","rt",stdin);
    // freopen("output.txt","wt",stdout);
    char *sep = "";
    while (scanf("%d", &n), n) {
        unsigned char *s = str;
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            s += strlen((char *) s);
            *s++ = i + 128;
        }
        *s = 0;
        build();
        vid++;
        mx = 0;
        for (int i = 0; i < numOfNodes; i++) {
            auto res = solve(i);
            if (res.count() > (n / 2)) mx = max(mx, len[i]);
        }
        printf(sep);
        sep = "\n";

        if (mx == 0) puts("?");
        else {
            vid++;
            dfs(0);
        }
    }

    return 0;
}
