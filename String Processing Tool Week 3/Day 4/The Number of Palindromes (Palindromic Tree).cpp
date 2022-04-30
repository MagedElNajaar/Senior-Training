//https://vjudge.net/contest/489655#problem/E
#include<bits/stdc++.h>

#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7, OO = 0x3f3f3f3f;
const ll LOO = 0x3f3f3f3f3f3f3f3f;
const long double EPS = 1e-8;

#define arrRange(t, a, mn, mx) t a##_[mx-mn+1], *a=(a##_)-mn;
#define arrRange2D(t, a, mn, mx, d) typedef t _##a[d]; arrRange(_##a, a, mn, mx)

const int N = 5e5 + 5, ALPHA = 256;

int numOfNodes, lstNode;
arrRange(int, pos, -1, N);
arrRange(int, len, -1, N);
arrRange(int, fail, -1, N);
arrRange(unsigned char, str, -1, N);
arrRange2D(unsigned char, childChars, -1, N, ALPHA);
arrRange(int, childSz, -1, N);
arrRange2D(int, child, -1, N, ALPHA);

int createNode(int l, int p) {
    pos[numOfNodes] = p;
    len[numOfNodes] = l;
    childSz[numOfNodes] = 0;
    memset(child[numOfNodes], -1, sizeof(child[numOfNodes]));
    return numOfNodes++;
}

void init() {
    lstNode = numOfNodes = -1;
    createNode(-1, -2);
    createNode(0, -1);
    fail[0] = -1;
}

void addEdge(int f, int t, char ch) {
    child[f][ch] = t;
    childChars[f][childSz[f]++] = ch;
}

int getFail(int node, int idx) {
    char ch = str[idx];
    int m;
    while (1) {
        m = idx - len[node] - 1;
        if (ch == str[m]) break;
        node = fail[node];
    }
    return node;
}


void addChar(int idx) {
    int node = getFail(lstNode, idx);
    char ch = str[idx];
    int &nxt = child[node][ch];
    if (~nxt) {
        lstNode = nxt;
        return;
    }
    lstNode = nxt = createNode(len[node] + 2, idx);
    if (!~node) {
        fail[nxt] = 0;
        return;
    }
    addEdge(node, nxt, ch);
    node = getFail(fail[node], idx);
    fail[nxt] = child[node][ch];
}


void print() {
    for (int i = -1; i < numOfNodes; i++) {
        for (int k = 0; k < childSz[i]; k++) {
            char ch = childChars[i][k];
            int j = child[i][ch];
            printf("%d,%d,%d,%d %d,%d,%d,%d %c\n", i, pos[i], len[i], fail[i], j, pos[j], len[j], fail[j], ch);
        }
    }
}

void build() {
    init();
    for (int i = 0; str[i]; i++) {
        addChar(i);
    }
}


int main() {
    FIO
    // freopen("input.txt","rt",stdin);
    // freopen("output.txt","wt",stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str);
        build();
        cout << "Case #" << i << ": " << numOfNodes - 1 << endl;
    }
    return 0;
}
