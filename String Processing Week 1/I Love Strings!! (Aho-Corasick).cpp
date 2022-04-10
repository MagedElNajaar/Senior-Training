#include <bits/stdc++.h>

using namespace std;
const int N = int(1e6) + 9, ALPHA = 128;
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
int names[N];
int main() {
    int n, q;
    cin >> n;
    while (n--) {
        init();
        cin >> str >> q;
        for (int i = 0; i < q; i++) {
            cin >> pat;
            names[i] = insert(pat, i);
        }
        //printTrie();
        computeFail();
        auto ret = match(q);
        for(int i = 0;i<q;i++){
            auto &res = ret[names[i]];
            cout << (res.size() ? 'y' : 'n') << "\n";
        }

    }
    return 0;
}
/*int main() {
    init();
    insert("she", 0);
    insert("e", 1);
    insert("help", 2);
    computeFail();
    strcpy(str, "shelp");
    auto ret = match(3);
    for (auto &x: ret) {
        for (auto &y: x)
            cout << y << " ";
        cout << "\n";
    }
    printTrie();
}*/
