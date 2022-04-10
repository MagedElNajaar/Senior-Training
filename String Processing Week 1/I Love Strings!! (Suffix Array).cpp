#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 9 + 1e3;
char str[N];
int suff[N], rnk[N], newRank[N], len;

void buildSuffix() {

    for (len = 0; !len || str[len - 1]; len++) {
        suff[len] = len;
        rnk[len] = str[len];
    }
    int h = 1;
    do {
        auto cmp = [h](int a, int b) {
            return rnk[a] < rnk[b] || rnk[a] == rnk[b] && rnk[a + h] < rnk[b + h];
        };
        sort(suff, suff + len, cmp);
        newRank[0] = 0;
        for (int i = 1; i < len; i++)
            newRank[i] = newRank[i - 1] + cmp(suff[i - 1], suff[i]);
        for (int i = 0; i < len; i++)
            rnk[suff[i]] = newRank[i];
        h <<= 1;
    } while (newRank[len - 1] != len - 1);
}

int main() {
    int t, q;
    cin >> t;
    while (t--) {
        cin >> str >> q;
        buildSuffix();
        suff[len] = len;
        while (q--) {
            char *pat = str + len;
            cin >> pat;
            int st = 0, ed = len;
            for (int i = 0; pat[i]; i++) {
                auto cmp = [i](int a, int b) {
                    return str[a + i] < str[b + i];
                };
                st = lower_bound(suff + st, suff + ed, len, cmp) - suff;
                ed = upper_bound(suff + st, suff + ed, len, cmp) - suff;
            }
            cout << (st < ed ? 'y' : 'n') << endl;
        }
    }
    return 0;
}
