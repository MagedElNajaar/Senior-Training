//https://vjudge.net/contest/488773#problem/AA
#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 9;
char str[N];
int suff[N], rnk[N], newRank[N], len;
int lcp[N];

void buildLcp() {
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        int j = suff[rnk[i] - 1];
        while (str[i + cnt] == str[j + cnt]) cnt++;
        lcp[rnk[i]] = cnt;
        if (cnt) cnt--;
    }

}

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
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);
        buildSuffix();
        buildLcp();
        printf("%lld\n", len * (len - 1ll) / 2 - accumulate(lcp, lcp + len, 0ll));
    }
    return 0;
}
