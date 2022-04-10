#include <bits/stdc++.h>


using namespace std;
const int N = 109, ALPHA = 128;
char str[int(1e5) + 9], pat[int(1e3) + 9], childChars[N][ALPHA];
int child[N][ALPHA], fail[N], nxt[N], patID[N], cCharsSz[N], numNodes;

int addNode() {
    memset(child[numNodes], -1, sizeof child[numNodes]);
    patID[numNodes] = -1;
    cCharsSz[numNodes] = 0;
    return numNodes++;
}

void init() {
    numNodes = 0;
    addNode();
}

int insert(char *pat, int ID) {
    int cur;
    for (cur = 0; *pat; pat++) {
        char c = *pat;
        int &nd = child[cur][c];
        if (!~nd) {
            nd = addNode();
            childChars[cur][cCharsSz[cur]++] = c;
        }
        cur = nd;
    }
    return ~patID[cur] ? patID[cur] : (patID[cur] = ID);
}

int nxtF(int f, char c) {
    while (!~child[f][c])
        f = fail[f];
    f = child[f][c];
    return f;
}

void computeFail() {
    queue<int> q;
    for (int i = 0; i < ALPHA; i++) {
        int &nd = child[0][i];
        if (~nd)
            fail[nd] = nxt[nd] = 0, q.push(nd);
        else nd = 0;
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < cCharsSz[u]; i++) {
            char c = childChars[u][i];
            int v = child[u][c];
            fail[v] = nxt[v] = nxtF(fail[u], c);
            q.push(v);
        }
    }
}

int Nxt(int u) {
    if (!u) return u;
    int &v = nxt[u];
    return ~patID[v] ? v : v = Nxt(v);
}

vector<vector<int>> match(int numPat) {
    vector<vector<int>> ret(numPat);
    int cur = 0;
    for (int i = 0; str[i]; i++) {
        char c = str[i];
        cur = nxtF(cur, c);
        for (int p = cur; p; p = Nxt(p)) {
            int x = patID[p];
            if (~x) ret[x].push_back(i);
        }
    }
    return ret;
}

void printTrie() {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < cCharsSz[i]; j++) {
            char c = childChars[i][j];
            int x = child[i][c];
            cout << i << "," << nxt[i] << " " << x << "," << nxt[x] << " " << c << endl;
        }
    }
    for (int i = 1; i < numNodes; i++) {
        int x = fail[i];
        cout << i << "," << nxt[i] << " " << x << "," << nxt[x] << endl;
    }

}


vector<int> names[N];
long long memo[N][26][1 << 10];
int m;

long long solve(int u, int rem, int mask) {
    if (!rem) return mask == (1 << m) - 1;
    long long &ret = memo[u][rem][mask];
    if (~ret) return ret;
    ret = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        int v = nxtF(u, c);
        int newMask = mask;
        for (int p = v; p; p = Nxt(p)) {
            int x = patID[p];
            if (~x)
                for (auto &y: names[x])
                    newMask |= 1 << y;
        }
        ret += solve(v, rem - 1, newMask);
    }
    return ret;
}

void build(int u, int rem, int mask, const string &s = "") {
    if (!rem) return cout << s << endl, void();
    for (char c = 'a'; c <= 'z'; c++) {
        int v = nxtF(u, c);
        int newMask = mask;
        for (int p = v; p; p = Nxt(p)) {
            int x = patID[p];
            if (~x)
                for (auto &y: names[x])
                    newMask |= 1 << y;
        }
        if (solve(v, rem - 1, newMask)) build(v, rem - 1, newMask, s + c);
    }
}

int main() {
    int n, cnt = 1;
    while (cin >> n >> m, n or m) {
        init();
        fill(names,names+m,vector<int>());
        for (int i = 0; i < m; i++) {
            cin >> pat;
            names[insert(pat, i)].push_back(i);
        }
        computeFail();
        memset(memo, -1, sizeof memo);
        long long res = solve(0, n, 0);
        cout << "Case " << cnt++ << ": " << res << " suspects" << endl;
        if (res <= 42) build(0, n, 0);
    }
    return 0;
}
