//https://vjudge.net/contest/489655#problem/A
#include <bits/stdc++.h>

#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7, OO = 0x3f3f3f3f;
const ll LOO = 0x3f3f3f3f3f3f3f3f;
const long double EPS = 1e-8;

#define arrRange(t, a, mn, mx) t a##_[mx-mn+1], *a=(a##_)-mn;
#define arrRange2D(t, a, mn, mx, d) typedef t _##a[d]; arrRange(_##a, a, mn, mx)

const int N = 2e5 + 5, ALPHA = 26;

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

unsigned char parC[N];
int parN[N];

void addChar(unsigned char c) {
    c-='A';
    int cur = addNode(), p;
    len[cur] = len[lstNode] + 1;
    parC[cur] = c;
    parN[cur] = lstNode;
    for (p = lstNode; !~child[p][c]; p = fail[p]) {
        addEdge(p, cur, c);
    }
    int q = child[p][c];
    if (len[p] + 1 == len[q]) fail[cur] = q;
    else {
        int clone = addNode();
        len[clone] = len[p] + 1;
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

ll memo[N], vis[N], vid;

ll solve(int nid) {
    ll &ret = memo[nid];
    if (vis[nid] == vid) return ret;
    ret = 1;
    vis[nid] = vid;
    for (int k = 0; k < childSz[nid]; k++) {
        unsigned char c = childChars[nid][k];
        int j = child[nid][c];
        ret += solve(j);
    }
    return ret;
}

void printPref(int nid) {
    if (nid) {
        printPref(parN[nid]);
        printf("%c", parC[nid]);
    }
}

int main() {
    FIO
    // freopen("input.txt","rt",stdin);
    // freopen("output.txt","wt",stdout);
    int n;
    scanf("%d", &n);
    scanf("%s%s", str, str + n + 1);
    int u = 0, mx = 0, bestU, l = 0;
    unsigned char *bestS;
    build();
    for (unsigned char *s = str + n + 1; *s; s++) {
        while (child[u][*s-'A'] == -1) {
            u = fail[u];
            l = len[u];

        }
        u = child[u][*s-'A'];
        l++;
        if (l > mx)
            mx = l, bestS = s;
    }
    *++bestS = 0;
    printf((char *) bestS - mx);
    return 0;
}
