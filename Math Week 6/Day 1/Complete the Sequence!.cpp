//https://vjudge.net/contest/495976#problem/D

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 5e4 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;

void babbage(vector<vector<int>> &table, int n) {
    int i = 0;
    bool same;
    if (table[0].size() > 1)
        do {
            same = true;
            vector<int> nxt, &cur = table[i++];
            for (int j = 1; j < cur.size(); j++) {
                nxt.push_back(cur[j] - cur[j - 1]);
                same &= nxt[0] == nxt.back();
            }
            table.push_back(nxt);
            n--;
        } while (!same);
    table.back().resize(n, table.back().back());
    for (; i; --i) {
        auto &cur = table[i], &nxt = table[i - 1];
        while (nxt.size() <= cur.size()) {
            int j = nxt.size() - 1;
            nxt.push_back(nxt[j] + cur[j]);
        }
    }

}

int main() {
    int n, m, t, x, tc = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        vector<vector<int>> table(1);
        for (int i = 0; i < n; i++) scanf("%d", &x), table.back().push_back(x);
        babbage(table, n + m);
        for (int i = n; i < table[0].size(); i++)
            printf("%d%c", table[0][i], " \n"[i + 1 == table[0].size()]);

    }
    return 0;
}
